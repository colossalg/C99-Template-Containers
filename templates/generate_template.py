import argparse
import json
import sys

def generate_template(
    src_file,
    dst_file,
    type_name,
    template_header,
    additional_abs_headers,
    additional_rel_headers
):
    with open(src_file, 'r') as ifstream:
        with open(dst_file, 'w') as ofstream:
            for line in ifstream:
                processed = (
                    line
                    .rstrip(''.join([' ', '\\', '\n']))
                    .replace('<typename>', type_name)
                    .replace('<template_header>', template_header)
                    .replace('<additional_abs_headers>', additional_abs_headers)
                    .replace('<additional_rel_headers>', additional_rel_headers)
                )
                ofstream.write(processed)
                ofstream.write('\n')

def create_headers_str(headers, beg_delim, end_delim):
    additional_abs_headers = ''
    for header in headers:
        additional_abs_headers += f'#include {beg_delim}{header}{end_delim}\n'
    return additional_abs_headers

parser = argparse.ArgumentParser()
parser.add_argument('--config_file', default=None)
parser.add_argument('--src_file')
parser.add_argument('--dst_file')
parser.add_argument('--template_header', default='')
parser.add_argument('--additional_abs_header', default=[], action='append')
parser.add_argument('--additional_rel_header', default=[], action='append')
parser.add_argument('--type_name')
args = parser.parse_args(sys.argv[1:])

if args.config_file:
    with open(args.config_file) as ifstream:
        configs = json.loads(ifstream.read())
        for c in configs:
            generate_template(
                c['src_file'],
                c['dst_file'],
                c['type_name'],
                c['template_header'] if 'template_header' in c else '',
                create_headers_str(c['additional_abs_headers'], '<', '>') if 'additional_abs_headers' in c else '',
                create_headers_str(c['additional_rel_headers'], '"', '"') if 'additional_rel_headers' in c else '',
            )
else:
        generate_template(
            args.src_file,
            args.dst_file,
            args.type_name,
            args.template_header,
            create_headers_str(args.additional_abs_header, '<', '>'),
            create_headers_str(args.additional_rel_header, '"', '"'),
        )
