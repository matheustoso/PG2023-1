import cv2 as cv
import numpy as np

dog = cv.imread('dog.jpg')
#Path absoluto necessário para macOS
# dog = cv.imread('/Users/matheustoso/Unisinos/2023:1/Processamento_Gráfico/Repo/PG2023-1/entregas/lists/list 4/dog.jpg')

dog = cv.Sobel(dog,cv.CV_64F,0,1,ksize=5)

cv.imshow('dog',dog)

cv.waitKey(0)

cv.destroyAllWindows()