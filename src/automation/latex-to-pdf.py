import re

def merge_cells(schedule):
    merged_schedule = []
    prev_row = []
    for row in schedule:
        if prev_row and row[0] == prev_row[0]:
            prev_row[-1] += ' ' + row[-1]
        else:
            merged_schedule.append(row)
            prev_row = row
    return merged_schedule

def format_schedule_table(table):
    # Extract the schedule part from the table
    schedule_part = table[table.index("\\multicolumn{1}{|c|}{\\textbf{SEG}}"):]
    # Remove the last row containing the address
    schedule_part = schedule_part[:schedule_part.index("\\end{tabularx}")]
    # Split the schedule into rows
    rows = re.split(r" \\\\[ \w+pt]* \n", schedule_part)

    # Process each row to extract the cells
    schedule = []
    for row in rows:
        cells = re.findall(r"\{(.+?)\}", row)
        schedule.append(cells)

    # Merge consecutive cells with the same class and teacher
    merged_schedule = merge_cells(schedule)

    # Format the merged schedule back into table rows
    formatted_rows = [r" & ".join(row) + r" \\" for row in merged_schedule]

    # Replace the original schedule rows with the formatted rows
    formatted_table = table[:table.index("\\multicolumn{1}{|c|}{\\textbf{SEG}}")]
    formatted_table.extend(formatted_rows)
    formatted_table.extend(table[table.index("\\end{tabularx}"):])
    return formatted_table

# Read the .tex file
with open("data/output/horario.tex", "r") as file:
    tex_content = file.read()

# Extract each schedule table from the .tex file
tables = re.findall(r"\\begin{tabularx}{\\textwidth}[^}]+\\end{tabularx}", tex_content)

# Format and print each schedule table
for table in tables:
    formatted_table = format_schedule_table(table)
    print(formatted_table)
    print("\n" + "=" * 80 + "\n")  # Separator between tables
