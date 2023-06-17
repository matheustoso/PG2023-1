import cv2 as cv
import numpy as np

dog = cv.imread('dog.jpg')
#Path absoluto necessário para macOS
# dog = cv.imread('/Users/matheustoso/Unisinos/2023:1/Processamento_Gráfico/Repo/PG2023-1/entregas/lists/list 4/dog.jpg')

for i in range(dog.shape[0]): #percorre linhas
	for j in range(dog.shape[1]): #percorre colunas
		dog.itemset((i,j,0),dog.item(i,j,0)^255) # canal B
		dog.itemset((i,j,1),dog.item(i,j,1)^255) # canal G
		dog.itemset((i,j,2),dog.item(i,j,2)^255) # canal R
		
# Média aritmética        
cv.imshow('dog',dog)

cv.waitKey(0)
cv.destroyAllWindows()