import cv2 as cv
import numpy as np

dog = cv.imread('dog.jpg')
#Path absoluto necessário para macOS
# dog = cv.imread('/Users/matheustoso/Unisinos/2023:1/Processamento_Gráfico/Repo/PG2023-1/entregas/lists/list 4/dog.jpg')

dog = dog[0:256, 128:384]
dog = cv.resize(dog, dsize=(1024, 1024))

cv.imshow('dog',dog)

cv.waitKey(0)
cv.destroyAllWindows()