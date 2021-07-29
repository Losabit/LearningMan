import os
import logging
import boto3

from function import *
from pathlib import Path
from botocore.exceptions import ClientError


if __name__ == '__main__':
    path = Path("resources")
    path.mkdir(parents=True, exist_ok=True)
    endGamePourcentage()
    plotByDeathPosition()
    plotByTimeWinning()
    plotKillsByTimes()
    plotScoreByTimes()
    plotPlayersByScore()
    endGamePourcentageIA()
    plotByDeathPositionAI()
    plotByTimeWinningAI()
    plotKillsByTimesAI()
    plotScoreByTimesAI()
    plotPlayersByScoreAI()
    plotByTimeWinningAI()
    plotByTimeWinning()
    
    s3 = boto3.client('s3')

    for file in os.listdir(str(path)):
        try:
            s3.upload_file(str(path) + '/' + file, bucket, 'reporting_results/{}'.format(file))
            logger.info(file + " successfully uploaded")
        except ClientError as err:
            logger.error(err)
