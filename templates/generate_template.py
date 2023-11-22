import argparse
import io
import json
import os
import sys

class TemplateClass:
    def __init__(self, typeinfo, source_template_file, header_template_file):
        self.typeinfo = typeinfo
        self.source_template_file = source_template_file
        self.header_template_file = header_template_file
        self.dependencies = []

    def __eq__(self, other):
        return (
            self.__class__.__name__ == other.__class__.__name__ and
            self.typeinfo == other.typeinfo
        )

    def __str__(self):
        return f'<{self.__class__.__name__} typename={self.typename}>'

    def getProcessedLine(self, line):
        processed = line.rstrip(''.join([' ', '\\', '\n'])) + '\n'
        for key, val in self.typeinfo.items():
            processed = processed.replace(f'<{key}>', val)
        return processed

    def getProcessedFileContents(self, file):
        contentStream = io.StringIO()
        for line in file:
            contentStream.write(self.getProcessedLine(line))
        contentStream.write('\n')
        return contentStream.getvalue()

    def getProcessedSourceContents(self, src_dir):
        if self.source_template_file is None:
            return ''
        with open(os.path.join(src_dir, self.source_template_file), 'r') as f:
            return self.getProcessedFileContents(f)

    def getProcessedHeaderContents(self, src_dir):
        with open(os.path.join(src_dir, self.header_template_file), 'r') as f:
            return self.getProcessedFileContents(f)

class Optional(TemplateClass):
    def __init__(self, typename):
        super().__init__(
            { 'typename': typename },
            None,
            'optional.template.h'
        )

class Pair(TemplateClass):
    def __init__(self, typeinfo):
        super().__init__(
            typeinfo,
            None,
            'pair.template.h'
        )

    def getTemplateTypeName(self):
        return f'pair_of_{self.typeinfo["typename_1"]}_and_{self.typeinfo["typename_2"]}'

class ArrayQueue(TemplateClass):
    def __init__(self, typename):
        super().__init__(
            { 'typename': typename },
            'array_queue.template.c',
            'array_queue.template.h'
        )
        self.dependencies = [Optional(typename)]

class ArrayStack(TemplateClass):
    def __init__(self, typename):
        super().__init__(
            { 'typename': typename },
            'array_stack.template.c',
            'array_stack.template.h'
        )
        self.dependencies = [Optional(typename)]

class LinkedList(TemplateClass):
    def __init__(self, typename):
        super().__init__(
            { 'typename': typename },
            'linked_list.template.c',
            'linked_list.template.h'
        )

class HashTable(TemplateClass):
    def __init__(self, typeinfo):
        super().__init__(
            typeinfo,
            'hash_table.template.c',
            'hash_table.template.h'
        )
        pair_dep = Pair({
            'typename_1': typeinfo['key_type'],
            'typename_2': typeinfo['val_type']
        })
        self.dependencies = [
            pair_dep,
            LinkedList(f'{pair_dep.getTemplateTypeName()}')
        ]


parser = argparse.ArgumentParser()
parser.add_argument('--config_file', default=None)
args = parser.parse_args(sys.argv[1:])

with open(args.config_file, 'r') as config_file:
    config = json.loads(config_file.read())

    templates = []
    for typename in config['optional']:
        templates.append(Optional(typename))
    for typename in config['array_queue']:
        templates.append(ArrayQueue(typename))
    for typename in config['array_stack']:
        templates.append(ArrayStack(typename))
    for typename in config['linked_list']:
        templates.append(LinkedList(typename))
    for typeinfo in config['hash_table']:
        templates.append(HashTable(typeinfo))

    # Resolve dependencies (crude, not sure about cycles)
    while True:
        dependencies = []
        for t in templates:
            for t_d in t.dependencies:
                if (
                    t_d not in templates and
                    t_d not in dependencies
                ):
                    dependencies.append(t_d)
        if len(dependencies) == 0:
            break
        templates = dependencies + templates

    src_dir = config['src_dir']
    dest_dir = config['dest']['dir']
    dest_c = config['dest']['.c']
    dest_h = config['dest']['.h']

    with open(os.path.join(dest_dir, dest_c), 'w') as c_contents:
        with open(os.path.join(src_dir, 'template_header.template.c'), 'r') as th_c:
            c_contents.write(th_c.read())
            c_contents.write('\n\n')
        c_contents.write(f'#include "{dest_h}"\n')
        c_contents.write('\n')
        for t in templates:
            c_contents.write(t.getProcessedSourceContents(src_dir))
        with open(os.path.join(src_dir, 'template_footer.template.c'), 'r') as tf_c:
            c_contents.write(tf_c.read())
            c_contents.write('\n')    

    with open(os.path.join(dest_dir, dest_h), 'w') as h_contents:
        with open(os.path.join(src_dir, 'template_header.template.h'), 'r') as th_h:
            h_contents.write(th_h.read())
            h_contents.write('\n')
        for abs_h in config['additional_absolute_headers']:
            h_contents.write(f'#include <{abs_h}>\n')
        h_contents.write('\n')
        for rel_h in config['additional_relative_headers']:
            h_contents.write(f'#include "{rel_h}"\n')
        h_contents.write('\n')
        for t in templates:
            h_contents.write(t.getProcessedHeaderContents(src_dir))
        with open(os.path.join(src_dir, 'template_footer.template.h'), 'r') as tf_h:
            h_contents.write(tf_h.read())
            h_contents.write('\n')