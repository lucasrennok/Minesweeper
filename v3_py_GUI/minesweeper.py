from random import randint

class pointMatrix:
	def __init__(self,mine,unlocked,flag,mines_around):
		self.mine = mine
		self.unlocked = unlocked
		self.flag = flag
		self.mines_around = mines_around

class Minesweeper:
	def __init__(self,dificuldade):
		if(dificuldade==1):
			self.x=8
			self.y=8
			self.mines=10
			print("\n_Easy Selected_")
		elif(dificuldade==2):
			self.x=16
			self.y=16
			self.mines=40 
			print("\n_Intermediate Selected_")
		elif(dificuldade==3):
			self.x=16
			self.y=30
			self.mines=99
			print("\n_Expert Selected_")
		print("\nGenerating the matrix...\n")
		self.matrix = []
		test = []
		for i in range(self.x):
			for j in range(self.y):
				test+=[pointMatrix(False,False,False,0)]
			self.matrix += [test]
			test = []
		m = self.mines
		while(m>0):
			i = randint(0,self.x-1)
			j = randint(0,self.y-1)
			if(self.matrix[i][j].mine==False):
				print("-Okay Mine-")
				self.matrix[i][j].mine = True
				m-=1
		print("MINES OKAY. Calculing mines around the points...\n")
		for i in range(self.x):
			for j in range(self.y):
				if(self.matrix[i][j].mine==True):
					self.matrix[i][j].mines_around=1
				else:
					if(i-1>=0 and j-1>=0):
						if(self.matrix[i-1][j-1].mine==True):
							self.matrix[i][j].mines_around+=1
					if(i-1>=0):
						if(self.matrix[i-1][j].mine==True):
							self.matrix[i][j].mines_around+=1
					if(i-1>=0 and j+1<self.y):
						if(self.matrix[i-1][j+1].mine==True):
							self.matrix[i][j].mines_around+=1
					if(j+1<self.y):
						if(self.matrix[i][j+1].mine==True):
							self.matrix[i][j].mines_around+=1
					if(i+1<self.x and j+1<self.y):
						if(self.matrix[i+1][j+1].mine==True):
							self.matrix[i][j].mines_around+=1
					if(i+1<self.x):
						if(self.matrix[i+1][j].mine==True):
							self.matrix[i][j].mines_around+=1
					if(i+1<self.x and j-1>=0):
						if(self.matrix[i+1][j-1].mine==True):
							self.matrix[i][j].mines_around+=1
					if(j-1>=0):
						if(self.matrix[i][j-1].mine==True):
							self.matrix[i][j].mines_around+=1
		print("Matrix generated.\n")

	def printaCampo(self, finalizado):
		str_aux = ""
		print("\nMinesweeper Game\n__ ", end="")
		for j in range(self.y):
			if(j<10):
				str_aux = " 0"+str(j)
				print(str_aux, end="")
			else:
				str_aux = " "+str(j)
				print(str_aux, end="")
		print("\n", end="")
		for i in range(self.x):
			if(i<10):
				str_aux = "0"+str(i)+"|"
				print(str_aux, end="")
			else:
				str_aux = str(i)+"|"
				print(str_aux, end="")
			for j in range(self.y):
				if(self.matrix[i][j].unlocked==True or finalizado>0):
					if(self.matrix[i][j].mine==False):
						if(self.matrix[i][j].mines_around!=-1):
							str_aux = " "+str(self.matrix[i][j].mines_around)+" "
							print(str_aux, end="")
						else:
							str_aux = " 0 "
							print(str_aux, end="")
					else:
						str_aux = " * "
						print(str_aux, end="")
				elif(self.matrix[i][j].flag==True):
					str_aux = " B "
					print(str_aux, end="")
				else:
					str_aux = " # "
					print(str_aux, end="")
			print("\n", end="")
		print("\n", end="")

	def decisaoJogador(self, linha, coluna, escolha):
		if(linha>=0 and linha<self.x and coluna>=0 and coluna<self.y):
			if(escolha==2):
				if(self.matrix[linha][coluna].unlocked==False):
					if(self.matrix[linha][coluna].flag==False):
						self.matrix[linha][coluna].flag=True
					else:
						self.matrix[linha][coluna].flag=False
			else:
				self.matrix[linha][coluna].unlocked=True
				if(self.matrix[linha][coluna].mine==True):
					return 2
				elif(self.solved()):
					return 1
				self.matrix[linha][coluna].flag=False
				if(self.matrix[linha][coluna].mines_around==0):
					self.cleanZeros(linha,coluna)
		else:
			print("\n!__!Invalid Values!__!\n")
		return 0

	def cleanZeros(self,linha, coluna):
		if(self.matrix[linha][coluna].mines_around==0):
			self.matrix[linha][coluna].mines_around=-1
			self.matrix[linha][coluna].unlocked=True
			self.matrix[linha][coluna].flag=False
			if(linha-1>=0):
				self.matrix[linha-1][coluna].unlocked=True
				if(self.matrix[linha-1][coluna].mines_around==0):
					self.cleanZeros(linha-1,coluna)
			if(coluna+1<self.y):
				self.matrix[linha][coluna+1].unlocked=True
				if(self.matrix[linha][coluna+1].mines_around==0):
					self.cleanZeros(linha,coluna+1)
			if(linha+1<self.x):
				self.matrix[linha+1][coluna].unlocked=True
				if(self.matrix[linha+1][coluna].mines_around==0):
					self.cleanZeros(linha+1,coluna)
			if(coluna-1>=0):
				self.matrix[linha][coluna-1].unlocked=True
				if(self.matrix[linha][coluna-1].mines_around==0):
					self.cleanZeros(linha,coluna-1)

	def solved(self):
		for i in range(self.x):
			for j in range(self.y):
				if(self.matrix[i][j].unlocked==False and self.matrix[i][j].mine==False):
					return False
		return True
