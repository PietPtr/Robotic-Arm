import pygame
import math
import sys
import os

pygame.init()

size = width, height = 1280, 720
black = 0, 0, 0
grey = 100, 100, 100
white = 255, 255, 255
red = 255, 100, 100

screen = pygame.display.set_mode(size)

view = [0, 0]
zoom = 1

# angles_list = [(130.573044, 203.515686),(128.349808, 203.328354),(126.181252, 203.016739),(124.074501, 202.581680),(122.036385, 202.024307),(120.073303, 201.346054),(118.191147, 200.548492),(116.395210, 199.633362),(114.690178, 198.602463),(113.080048, 197.457596),(111.568207, 196.200531),(110.157394, 194.832840),(108.849792, 193.355957),(107.647041, 191.770966),(106.550369, 190.078659),(105.560623, 188.279373),(104.678375, 186.372971),(103.904030, 184.358688),(103.237915, 182.235107),(102.680382, 180.000000),(102.231949, 177.650223),(101.893379, 175.181473),(101.665878, 172.588196),(101.551208, 169.863144),(101.551956, 166.997116),(101.671745, 163.978394),(101.915627, 160.791901),(102.290581, 157.418335),(102.806244, 153.832291),(103.476067, 150.000000),(104.319153, 145.875015),(105.363472, 141.391174),(106.651901, 136.449005),(108.254967, 130.887177),(108.254967, 130.887177),(106.651901, 136.449005),(105.363472, 141.391174),(104.319153, 145.875015),(103.476067, 150.000000),(102.806244, 153.832291),(102.290581, 157.418335),(101.915627, 160.791901),(101.671745, 163.978394),(101.551956, 166.997116),(101.551208, 169.863144),(101.665878, 172.588196),(101.893379, 175.181473),(102.231949, 177.650223),(102.680382, 180.000000),(103.237915, 182.235107),(103.904030, 184.358688),(104.678375, 186.372971),(105.560623, 188.279373),(106.550369, 190.078659),(107.647041, 191.770966),(108.849792, 193.355957),(110.157394, 194.832840),(111.568207, 196.200531),(113.080048, 197.457596),(114.690178, 198.602463),(116.395210, 199.633362),(118.191147, 200.548492),(120.073303, 201.346054),(122.036385, 202.024307),(124.074501, 202.581680),(126.181252, 203.016739),(128.349808, 203.328354),(130.573044, 203.515686),(132.843643, 203.578186)]

# print(os.popen("./test 5 4 3").read())

angles_list = []

for i in range(0, 75):
    result = os.popen("./test 5 0 " + str(i / 10)).read()
    shoulder = float(result.split(" ")[1])
    elbow = float(result.split(" ")[2])
    angles_list.append((shoulder,elbow))

for i in range(75, 0, -1):
    result = os.popen("./test 5 0 " + str(i / 10)).read()
    shoulder = float(result.split(" ")[1])
    elbow = float(result.split(" ")[2])
    angles_list.append((shoulder,elbow))


UPPER = 5
UNDER = 4
TO_DEG = 57.2957795

pointlists = []


def angles_to_points(shoulder, elbow):
    x1 = math.cos(math.radians(180 - shoulder)) * UPPER
    y1 = math.sin(math.radians(180 - shoulder)) * UNDER

    b = 180 - 90 - (180 - shoulder)
    a = math.radians(180 - b - elbow)
    x2 = x1 + math.cos(a) * UNDER;
    y2 = y1 + math.sin(a) * UNDER;

    scale = 35
    offset = (500, 600)
    points = [offset]
    points.append((offset[0] + x1 * scale, offset[1] + -y1 * scale))
    points.append((offset[0] + x2 * scale, offset[1] + -y2 * scale))

    return points


frame = 0
index = 0

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()
        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                index = (index + 1) % len(angles_list)
            if event.button == 2:
                index = (index - 1) % len(angles_list)

    """
    Updates and logic
    """
    mov = pygame.mouse.get_rel()
    if (pygame.mouse.get_pressed()[0]):
        view[0] += mov[0] * 1 / zoom
        view[1] += mov[1] * 1 / zoom

    """
    Drawing
    """
    screen.fill(black)

    angle = angles_list[int(frame / 5) % len(angles_list)]
    # angle = angles_list[index]

    pygame.draw.lines(screen, white, False, \
        angles_to_points(angle[0], angle[1]))


    # pygame.draw.line(screen, grey, (500 + 35 * 5, 720), (500 + 35 * 5, 0))

    pygame.display.flip()
    frame += 1
