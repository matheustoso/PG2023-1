import cv2 as cv
import numpy as np

dog = cv.imread('dog.jpg')
#Path absoluto necessário para macOS
# dog = cv.imread('/Users/matheustoso/Unisinos/2023:1/Processamento_Gráfico/Repo/PG2023-1/entregas/lists/list 4/dog.jpg')
dog2 = dog.copy()
dog3 = dog.copy()

for i in range(dog.shape[0]): #percorre linhas
	for j in range(dog.shape[1]): #percorre colunas
		media = dog.item(i,j,0) * 0.333 + dog.item(i,j,1) * 0.333 + dog.item(i,j,2) * 0.3333
		dog2.itemset((i,j,0),media) # canal B
		dog2.itemset((i,j,1),media) # canal G
		dog2.itemset((i,j,2),media) # canal R

		mediaPond = dog.item(i,j,0) * 0.07 + dog.item(i,j,1) * 0.71 + dog.item(i,j,2) * 0.21
		dog3.itemset((i,j,0),mediaPond) # canal B
		dog3.itemset((i,j,1),mediaPond) # canal G
		dog3.itemset((i,j,2),mediaPond) # canal R
		
# Média aritmética        
cv.imshow('dog2',dog2)

cv.waitKey(0)

#Média ponderada
cv.imshow('dog3',dog3)

cv.waitKey(0)
cv.destroyAllWindows()