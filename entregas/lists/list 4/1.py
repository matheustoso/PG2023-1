import cv2 as cv
import numpy as np

dog = cv.imread('dog.jpg')
#Path absoluto necessário para macOS
# dog = cv.imread('/Users/matheustoso/Unisinos/2023:1/Processamento_Gráfico/Repo/PG2023-1/entregas/lists/list 4/dog.jpg')
dog2 = dog.copy()
dog3 = dog.copy()

# Vermelho
dog[:,:,0] = 0
dog[:,:,1] = 0

cv.imshow('red dog',dog)
cv.waitKey(0)

# Azul
dog2[:,:,1] = 0
dog2[:,:,2] = 0

cv.imshow('blue dog',dog2)
cv.waitKey(0)

# Verde
dog3[:,:,0] = 0
dog3[:,:,2] = 0

cv.imshow('green dog',dog3)

cv.waitKey(0)
cv.destroyAllWindows()