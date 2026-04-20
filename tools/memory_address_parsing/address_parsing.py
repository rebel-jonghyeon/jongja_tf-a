import pandas as pd
import tkinter as tk
from tkinter import filedialog

# 상수 정의
ADDRESS_BITS = 26
HEX_BASE = 16

def hex_to_bin(hex_str: str, bits: int) -> str:
	try:
		hex_str = hex_str.replace('0x', '')
		num = int(hex_str, HEX_BASE)
		return format(num, f'0{bits}b')
	except ValueError:
		return None

def parse_address(line: str, bin_str: str) -> dict:
	if bin_str is None or len(bin_str) != ADDRESS_BITS:
		return None

	# 2진수 문자열을 뒤집어서 LSB를 인덱스 0으로 설정
	bin_str_reversed = bin_str[::-1]

	# 2진수 문자열을 비트 단위로 배열에 저장
	la = [int(bit) for bit in bin_str_reversed]

	# RA (Row Address) 계산
	ra14 = int(la[24] & la[23] or la[25])
	ra13 = int((not la[24]) & (not la[25]) & ((not la[23]) or (not la[9])))
	ra12 = int(la[25] and la[9] or (not la[25]) and la[22])
	ra = [0] * 15
	ra[0:12] = la[10:22]
	ra[12:15] = [ra12, ra13, ra14]
	ra = ra[::-1] # ra를 뒤집기

	# SID 계산
	sid1 = (not la[9]) & (not la[25]) & ((la[23]) or la[24])
	sid0 = (not la[23]) & la[9] or la[25]
	sid = [int(sid0), int(sid1)]
	sid = sid[::-1] # sid를 뒤집기

	# BA (Bank Address) 및 CA (Column Address) 추출
	ba = [la[6], la[7], la[2], la[8]]
	ba = ba[::-1] # ba를 뒤집기

	ca = [la[0], la[1], la[3], la[4], la[5]]
	ca = ca[::-1] # ca를 뒤집기

	return {
		'address_hex': line,
		'address_bin': bin_str,
		'row_bin': ''.join(map(str, ra)),
		'row': int(''.join(map(str, ra)), 2),
		'sid_bin': ''.join(map(str, sid)),
		'sid': int(''.join(map(str, sid)), 2),
		'bank_bin': ''.join(map(str, ba)),
		'bank': int(''.join(map(str, ba)), 2),
		'col_bin': ''.join(map(str, ca)),
		'col': int(''.join(map(str, ca)), 2)
	}

def process_file(input_file: str, output_file: str) -> None:
	try:
		with open(input_file, 'r', encoding='utf-8', errors='ignore') as f:
			hex_lines = [line.strip() for line in f if line.strip()]

		parsed_addresses = []
		for line in hex_lines:
			bin_str = hex_to_bin(line, ADDRESS_BITS)
			if bin_str:
				parsed_address = parse_address(line, bin_str)
				if parsed_address:
					parsed_addresses.append(parsed_address)

		if parsed_addresses:
			df = pd.DataFrame(parsed_addresses)
			columns = ['address_hex', 'address_bin', 'row_bin', 'row', 'sid_bin', 'sid', 'bank_bin', 'bank', 'col_bin', 'col']
			df = df[columns] # 컬럼 순서 지정
			df.to_excel(output_file, index=False, engine='openpyxl')
			status_label.config(text="성공적으로 변환되었습니다!")
		else:
			status_label.config(text="파싱할 데이터가 없습니다.")
	except Exception as e:
		status_label.config(text=f"오류 발생: {e}")

def select_input_file() -> None:
	file_path = filedialog.askopenfilename(title="입력 파일 선택", filetypes=[("Text Files", "*.txt")])
	if file_path:
		input_entry.delete(0, tk.END)
		input_entry.insert(0, file_path)

def select_output_file() -> None:
	file_path = filedialog.asksaveasfilename(title="출력 파일 선택", defaultextension=".xlsx", filetypes=[("Excel Files", "*.xlsx")])
	if file_path:
		output_entry.delete(0, tk.END)
		output_entry.insert(0, file_path)

def start_processing() -> None:
	input_file = input_entry.get()
	output_file = output_entry.get()
	if input_file and output_file:
		process_file(input_file, output_file)
	else:
		status_label.config(text="입력 파일과 출력 파일을 모두 선택하세요.")

root = tk.Tk()
root.title("16진수 address parsing")

input_label = tk.Label(root, text="입력 파일:")
input_label.grid(row=0, column=0, padx=5, pady=5)
input_entry = tk.Entry(root, width=50)
input_entry.grid(row=0, column=1, padx=5, pady=5)
input_button = tk.Button(root, text="찾아보기", command=select_input_file)
input_button.grid(row=0, column=2, padx=5, pady=5)

output_label = tk.Label(root, text="출력 파일:")
output_label.grid(row=1, column=0, padx=5, pady=5)
output_entry = tk.Entry(root, width=50)
output_entry.grid(row=1, column=1, padx=5, pady=5)
output_button = tk.Button(root, text="찾아보기", command=select_output_file)
output_button.grid(row=1, column=2, padx=5, pady=5)

process_button = tk.Button(root, text="변환 시작", command=start_processing)
process_button.grid(row=2, column=1, padx=5, pady=5)

status_label = tk.Label(root, text="")
status_label.grid(row=3, column=1, padx=5, pady=5)

root.mainloop()
