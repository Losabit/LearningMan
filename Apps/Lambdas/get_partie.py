import sys
import os
import logging
import pymysql
import base64

# rds settings
rds_host = "learningman-db.cqrratbcqklq.eu-west-3.rds.amazonaws.com"
name = os.environ['user']
password = os.environ['password']
db_name = os.environ['database']

# logging
logger = logging.getLogger()
logger.setLevel(logging.INFO)

try:
    conn = pymysql.connect(host=rds_host, user=name, passwd=password, db=db_name,  charset='utf8mb4', connect_timeout=5, port=3306)
except pymysql.Error as e:
    logger.error("ERROR: Unexpected error: Could not connect to MySql instance. " + e)
    sys.exit()

logger.info("SUCCESS: Connection to RDS mysql instance succeeded")



# executes upon API event
def lambda_handler(event, context):
    # array to store values to be returned
    records = []
    with conn.cursor() as cur:
        cur.execute("select * from partie")
        conn.commit()
        for row in cur:
            record = {
                'id': row[0],
                'date': str(row[1]),
                'elapsedTime': row[2],
                'isDead': row[3],
                'playerType': row[4],
                'scoreTotal': row[5],
                'nbKill': row[6],
                'deathPosition': row[7],
                'token': row[8],
                'idMap': row[9],
                'learningModel': row[10],
            }
            records.append(record)
        records.sort(key=lambda x: x['scoreTotal'], reverse=True)
        return records[:150]
