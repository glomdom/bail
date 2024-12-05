"""
Goes through every source file and prepends the GPLv3 licensing text.
"""

import os
from datetime import datetime

year = datetime.now().year

gpl_text = f"""/*
    Copyright (C) {year}  glomdom

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
"""

def add_gpl_to_file(file_path):
    with open(file_path, 'r') as file:
        content = file.read()
    
    if f"Copyright (C) {year}  glomdom" not in content:
        with open(file_path, 'w') as file:
            file.write(gpl_text + "\n" + content)

        print(f"Added GPLv3 to: {file_path}")
    else:
        print(f"GPLv3 already present in: {file_path}")

def add_gpl_to_directory(directory):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(('.hpp', '.cpp')):
                file_path = os.path.join(root, file)
                add_gpl_to_file(file_path)

add_gpl_to_directory("./src/")