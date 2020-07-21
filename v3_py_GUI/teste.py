
class pointMatrix:
	def __init__(self,mine,unlocked,flag,mines_around):
		self.mine = mine
		self.unlocked = unlocked
		self.flag = flag
		self.mines_around = mines_around
    


matrix = []
test = [pointMatrix(False,False,False,0)]*8
matrix += [test]*8

for i in range(8):
    for j in range(8):
        print(matrix[i][j].mines_around, end="")
    print("")
