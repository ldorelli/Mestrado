from __future__ import print_function
import os
import sys


class ProgressBar:
	def __init__(self, total_op, show_dif):
		self.total_op = total_op
		self.curr_op = 0
		self.last_show = 0
		self.p = 0
		self.show_dif = show_dif

	# Adds n_op number of operations to the current progresss
	def step(self, n_op):
		self.curr_op += n_op

	# Show a number progress bar, in the format text_b percentage text_after
	def show_bar(self, text_b, text_a):	
		b = '\b' * 1000
		p = round(self.curr_op/float(self.total_op)*100, 2)
		if p - self.last_show <= self.show_dif:
			return 
		print("\t\t\t\t", end="")
		print(b + text_b + str(p) + text_a, end="", file=sys.stderr)
		sys.stdout.flush()
		self.last_show = p

	# Returns the progress in percentage
	def get_progress(self):
		return round(self.curr_op/float(self.total_op)*100, 2)

if __name__ == '__main__':
	x = ProgressBar(100, 11)
	x.step(10)
	x.show_bar("Progress ", " done.")
	x.step(10)
	x.show_bar("Progress ", " done.")