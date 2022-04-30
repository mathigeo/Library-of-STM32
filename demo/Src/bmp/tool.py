import cv2 as cv

img=cv.imread("boot1.bmp",0)

ret,otsu=cv.threshold(img,0,255,cv.THRESH_BINARY+cv.THRESH_OTSU)

cv.imshow("img",img)
cv.imshow("otsu",otsu)

ret = cv.imwrite("./otsu.bmp",otsu)

cv.waitKey()
cv.destroyAllWindows()