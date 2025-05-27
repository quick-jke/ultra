import os
import re

def find_directory(root_dir, target_dir_name):
    for dirpath, dirnames, filenames in os.walk(root_dir):
        if target_dir_name in dirnames:
            return os.path.join(dirpath, target_dir_name)
    return None

def parse_model_file(file_path):
    with open(file_path, 'r') as f:
        content = f.read()
    
    
    entity_match = re.search(r'ENTITY\s+(\w+)\s*{', content)
    if not entity_match:
        return None, [], []  
    
    class_name = entity_match.group(1)
    
    
    imports = re.findall(r'IMPORT\s+(\w+);', content)
    
    
    fields = []
    field_pattern = re.compile(r'(?:ID\s+)?([a-zA-Z0-9_:<>, ]+?)\s+(\w+);')
    
    
    entity_start = content.find(f'ENTITY {class_name} {{')
    entity_end = content.find('};', entity_start)
    
    if entity_start == -1 or entity_end == -1:
        return class_name, imports, []  
    
    entity_content = content[entity_start:entity_end]
    
    for match in field_pattern.finditer(entity_content):
        field_type, field_name = match.groups()
        field_type = ' '.join(field_type.strip().split())
        fields.append((field_type, field_name))
    
    return class_name, imports, fields  

def scan_models():
    directory_name_to_find = "models"
    result_path = find_directory(os.getcwd(), directory_name_to_find)
    models_info = []
    
    if result_path:
        for filename in os.listdir(result_path):
            if filename.endswith('.entity.hpp'):
                file_path = os.path.join(result_path, filename)
                class_name, imports, fields = parse_model_file(file_path)
                if class_name:
                    models_info.append((filename, class_name, imports, fields))
    else:
        print(f"Directory '{directory_name_to_find}' not found in '{os.getcwd()}'")
    
    return models_info