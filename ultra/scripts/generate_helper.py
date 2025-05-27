import os
import sys
from scan_models import scan_models

def generate_session_code(models_info, output_file):
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    
    with open(output_file, 'w') as f:
        f.write("#pragma once\n")
        f.write("#include \"session.hpp\"\n")  

        for filename, class_name, imports, fields in models_info:
            f.write(f"#include \"{filename}\"\n")

        f.write("#include <iostream>\n")
        f.write("#include <string>\n\n")
        # f.write("#include \"sql_builder.hpp\"\n")
        f.write("namespace quick {\nnamespace ultra {\n\n")
        
        for filename, class_name, imports, fields in models_info:
            f.write(f"template<>\n")
            f.write(f"inline void Session::save<{class_name}>(const {class_name}& obj) {{\n")
            f.write(f'    std::cout << "Saving {class_name}:" << std::endl;\n')

            f.write('    std::vector<std::string> fields;\n')
            f.write('    std::vector<std::string> values;\n')
            for field_type, field_name in fields:
                if field_type.startswith('ID'):
                    continue
                f.write(f'    fields.push_back("{field_name}");\n')
                f.write(f'    values.push_back(obj.{field_name});\n')

            
            f.write(f'    std::string req = SQLBuilder::INSERT("{class_name}", fields, values);\n')

            f.write('    driver_->begin_transaction();\n')

            f.write('    try {\n')
            f.write('        std::cout << req << std::endl;\n')
            f.write('        driver_->execute(req);\n')
            f.write('        driver_->commit();\n')
            f.write('    } catch (const std::exception& e) {\n')
            f.write('        driver_->rollback();\n')
            f.write('        std::cerr << "Error creating tables: " << e.what() << std::endl;\n')
            f.write('        throw;\n')
            f.write('    }\n')
        
    
            
            
            f.write("}\n\n")
        
        f.write("}}\n")

if __name__ == "__main__":
    file_path = "build/generated/session_helper.hpp"  
    content = "Hello, World!"

    models_info = scan_models()

    if models_info:
        generate_session_code(models_info, file_path)
        print("Successfully generated session_helper.hpp")
    else:
        print("No models found to generate code")