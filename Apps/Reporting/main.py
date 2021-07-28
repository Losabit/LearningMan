import json
import os
import logging

from functions import *
from pathlib import Path
import boto3
from botocore.exceptions import ClientError

bucket = "learningman-project-website"
logger = logging.getLogger()
logger.setLevel(logging.INFO)

path = Path("resources")
path.mkdir(parents=True, exist_ok=True)
plot_by_end_pourcentage()
plot_by_death_position()
plot_by_time_winning()
plot_kills_by_time()
plot_scores_by_time()
plot_players_by_score()

s3 = boto3.client('s3')

for file in os.listdir(str(path)):
    try:
        s3.upload_file(str(path) + '/' + file, bucket, 'reporting_results/{}'.format(file))
        logger.info(file + " successfully uploaded")
    except ClientError as err:
        logger.error(err)
