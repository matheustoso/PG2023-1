import cv2 as cv
import numpy as np

dog = cv.imread('dog.jpg')
#Path absoluto necessário para macOS
# dog = cv.imread('/Users/matheustoso/Unisinos/2023:1/Processamento_Gráfico/Repo/PG2023-1/entregas/lists/list 4/dog.jpg')
dog = cv.cvtColor(dog,cv.COLOR_BGR2GRAY)
dog2 = dog.copy()

k = 120

for i in range(dog.shape[0]):
	for j in range(dog.shape[1]):
		if dog.item(i,j) < k:
			dog2.itemset((i,j),0)
		else:
			dog2.itemset((i,j),255)
		
# Média aritmética        
cv.imshow('dog',dog2)

cv.waitKey(0)
cv.destroyAllWindows()