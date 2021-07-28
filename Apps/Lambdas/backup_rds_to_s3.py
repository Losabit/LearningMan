import json
import logging
import time
import boto3
from datetime import datetime
from botocore.exceptions import ClientError


def lambda_handler(event, context):
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)
    
    db_name = 'learningman-db'
    s3_name = 'learningman-project-db-dumps'
    
    date = datetime.now().strftime("%d-%m-%Y-%Hh%Mm%Ss")
    logger.info(date)
    rds = boto3.client('rds')
    try:
        # Creating Snapshot
        
        response = rds.create_db_snapshot(
        DBSnapshotIdentifier='snapshot-' + db_name + '-' + date,
        DBInstanceIdentifier=db_name)
        logger.info(response)
        
        
        # Waiting to snapshot getting created
        
        time.sleep(300)
        
        
        # Export Snapshot to S3
        
        response_export = rds.start_export_task(
            ExportTaskIdentifier='export-' + db_name + '-' + date,
            SourceArn=response['DBSnapshot']['DBSnapshotArn'],
            S3BucketName=s3_name,
            IamRoleArn='arn:aws:iam::967781192615:role/service-role/backup_rds_to_s3-role-lsrt6zju',
            KmsKeyId='cccbfd9c-53e6-419a-a5ba-5e07e595785d')
            
        logger.info(response_export)
    except ClientError as err:
        logger.error(err)
    return {
        'statusCode': 200,
        'body': json.dumps('Success')
    }
