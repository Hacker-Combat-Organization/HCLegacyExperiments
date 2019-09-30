import boto3
print("Showing S3 Buckets")
s3 = boto3.resource('s3')
for bucket in s3.buckets.all():
	print(bucket.name)
