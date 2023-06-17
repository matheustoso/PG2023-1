import cv2 as cv
import numpy as np

dog = cv.imread('dog.jpg')
#Path absoluto necessário para macOS
# dog = cv.imread('/Users/matheustoso/Unisinos/2023:1/Processamento_Gráfico/Repo/PG2023-1/entregas/lists/list 4/dog.jpg')

dog = cv.cvtColor(dog, cv.COLOR_BGR2RGB)
dog = np.array(dog, dtype=np.float64)
dog = cv.transform(dog, np.matrix([[0.393, 0.769, 0.189],
                                   [0.349, 0.686, 0.168],
                                   [0.272, 0.534, 0.131]]))
dog[np.where(dog > 255)] = 255
dog = np.array(dog, dtype=np.uint8)
dog = cv.cvtColor(dog, cv.COLOR_RGB2BGR)

cv.imshow("sepia", dog)

cv.waitKey(0)

cv.destroyAllWindows()