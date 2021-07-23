from function import *
from pathlib import Path


if __name__ == '__main__':
    path = Path("resources")
    path.mkdir(parents=True, exist_ok=True)
    endGamePourcentage()
    plotByDeathPosition()
    plotByTimeWinning()
    plotKillsByTimes()
    plotScoreByTimes()
    plotPlayersByScore()