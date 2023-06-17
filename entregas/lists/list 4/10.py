import cv2 as cv
import numpy as np

dog = cv.imread('dog.jpg')
#Path absoluto necessário para macOS
# dog = cv.imread('/Users/matheustoso/Unisinos/2023:1/Processamento_Gráfico/Repo/PG2023-1/entregas/lists/list 4/dog.jpg')
dog2 = dog.copy()

kernel = np.ones((3,3),np.uint8)
dog = cv.dilate(dog,kernel,iterations=1)

cv.imshow('dilation',dog)

cv.waitKey(0)

dog2 = cv.erode(dog2,kernel,iterations=1)

cv.imshow('erosion',dog2)

cv.waitKey(0)

cv.destroyAllWindows()