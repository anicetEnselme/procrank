#!/usr/bin/python3
import argparse
import sys
MEGABYTE = 1024
file_path = '/proc/procrank'

# parser = argparse.ArgumentParser(description='Find the real memory mapped by a process')
# parser.add_argument('-p', '--pid', type=str, help="Show the amount of memory occupied by the specified pid")
# parser.add_argument('-u', '--uss', help="Show only USS", action="store_true")
# args = parser.parse_args()


def readFile(filename):
	"""This function reads some file and return its content as a list of list
	"""
	with open(filename, 'r') as file:
		return_lines = []
		lines = file.readlines()
		file.close()
		number_process = lines[-1]	
		lines = lines[3:50]
		#del lines[-1]
		for line in lines:
			return_lines.append(line.strip().split("|"))
		return return_lines


def getResumePerPid(process_uss:list)->dict:
	"""This function takes a list of list. It returns a dictionnary in which the key is the
	first element in the list and values are list of the remaining elements for each list in the initial list
	"""
	process_uss_dict = {}
	for line in process_uss:
		print("This is the line:", line)
		for i in range(2,6):
			line[i] = int(line[i])
			if line[i] > MEGABYTE:
				line[i] = str(round(line[i]/MEGABYTE,2))
				unit = 'M'
				#line[i] = str(line[i]).strip()
				line[i] += unit
			else:
				line[i] = str(line[i]).strip()
				unit = 'K'
				line[i] += unit
		process_uss_dict[int(line[0])] = line[1:]
	# for elmt in process_uss_dict:
	# 	print(elmt, process_uss_dict[elmt])
	return process_uss_dict


def showOneUss(process_uss:dict, pid:int):
	#print(type(pid))
	uss = process_uss.get(pid,-1)
	return uss[3] if uss != -1 else uss

def showAll(process_uss):
	print("="*62)
	print("%-5s %s %-20s %s %-6s %s %-6s %s %-6s %s %-6s "%("PID", "|", "PROCESS NAME", "|", "VSS", "|", "RSS", "|", "USS", "|", "PSS"))
	print("="*62)
	for pid in process_uss:
		print("%-5s %s %-20s %s %-6s %s %-6s %s %-6s %s %-6s "%(pid, "|", process_uss[pid][0], "|", process_uss[pid][1], "|", process_uss[pid][2], "|", process_uss[pid][3], "|", process_uss[pid][4]))

# def showUssOnly(process_uss:dict):
# 	print("="*50)
# 	print("%-18s %-16s %-14s %-12s %-10s "%("PID", "|", "PROCESS NAME", "|", "USS"))
# 	for pid in process_uss:
# 		print("%-18d %-16s %-14s %-12s %-10d "%(pid, "|", process_uss[pid][0], "|", process_uss[pid][3]))
# 	print("="*50)


if __name__ == '__main__':

	pid = sys.argv[1]
	size = sys.argv[2]
	print("on m'a appelé")
	with open('text.txt', 'w') as file:
		file.write("Juste un test!")
		file.close()
	#print("J'ai bien recu les arguments argv1: {} et argv2: {}".format(pid,size))
	# lines = readFile(file_path)
	# process_uss = getResumePerPid(lines)	
	# if args.pid:
	# 	uss = showOneUss(process_uss, int(args.pid))
	# 	# for pid in process_uss:
	# 	# 	print(pid, type(pid))
	# 	# print("argument:",args.pid, "type:", type(args.pid))
	# 	if uss == -1:
	# 		print("Pid not found!")
	# 		sys.exit(0)
	# 	else:
	# 		print(uss)
	# 		sys.exit(0)
	# if args.uss:
	# 	if args.pid:
	# 		print("Only one of p or u parameter is accepted!")
	# 		sys.exit(0)
	# 	showUssOnly(process_uss)
	# 	sys.exit(0)
	# showAll(process_uss)


