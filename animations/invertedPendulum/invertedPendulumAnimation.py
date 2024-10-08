import pygame
import csv
import math
import graphics

def load_data(file_path):
    data = []
    with open(file_path, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            data.append({
                "time": float(row['time']),
                "s": float(row['x[0]']),
                "v": float(row['x[1]']),
                "phi": -float(row['x[2]']) + 2*math.pi,
                "vphi": float(row['x[3]']),
                "tau": float(row['u[0]'])
            })
    return data

def main(data):
    T_F = data[-1]["time"]
    INTERVALS = len(data)
    FPS = 60  # Frames Per Second
    SHIFT = INTERVALS / (T_F * FPS)
    width = 1920
    height = 1080
    
    phis = []
    taus = []
    
    pygame.init()
    screen = pygame.display.set_mode(
        size=(width, height),
        flags=pygame.RESIZABLE)
    clock = pygame.time.Clock()

    pygame.event.set_blocked(None)
    pygame.event.set_allowed([pygame.QUIT, pygame.KEYDOWN])

    game_running = True
    paused = False

    dt = 1 / FPS
    time = 0
    FRAME = 0
    current_frame = 0
    total_frames = len(data)

    while game_running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_running = False

        if current_frame >= total_frames:
               dt = 1 / FPS
               time = 0
               FRAME = 0
               current_frame = 0  # Restart the animation

        s = data[current_frame]["s"]
        v = data[current_frame]["v"]
        phi = data[current_frame]["phi"]
        tau = data[current_frame]["tau"]
        phis.append(phi)
        taus.append(tau)  # u0 = tau
        t = data[current_frame]["time"] 
        graphics.redraw(screen, t, dt, 0, 0.25, s, v, taus, phis)
        pygame.display.flip()
        if len(phis) > 750:
            phis.pop(0)
            taus.pop(0)
        dt = clock.tick(FPS) / 1000
        time += dt
        FRAME += SHIFT
        current_frame = int(FRAME)
    pygame.quit()


if __name__ == "__main__":
    path = "/home/linus/masterarbeit/ipopt_do/examples/.generated/invertedPendulum"
    model = "invertedPendulum"
    it = 0
    file_path = path + "/" + model + str(it) + ".csv"
    data = load_data(file_path)
    main(data)

