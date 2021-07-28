import sys
import logging
import pymysql
import os
import json

# rds settings
rds_host = "learningman-db.cqrratbcqklq.eu-west-3.rds.amazonaws.com"
name = os.environ['user']
password = os.environ['password']
db_name = os.environ['database']

# logging
logger = logging.getLogger()
logger.setLevel(logging.INFO)

try:
    conn = pymysql.connect(host=rds_host, user=name, passwd=password, db=db_name, charset='utf8mb4', connect_timeout=5)
except:
    logger.error("ERROR: Unexpected error: Could not connect to MySql instance.")
    sys.exit()

logger.info("SUCCESS: Connection to RDS mysql instance succeeded")

def lambda_handler(event, context):
    
    with conn.cursor() as cur:
        sql = "INSERT INTO `user` (`token`, `pseudo`) VALUES (%s, %s)"
        cur.execute(sql, (event['token'], event['pseudo']))
        conn.commit()

    return {
        'statusCode': 200,
        'body': event,
    }