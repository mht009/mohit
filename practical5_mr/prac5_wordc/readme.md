javac -classpath ${HADOOP_HOME}/hadoop-core-1.2.1.jar WordCount.java
jar -cvf wc.jar WordCount*.class
<!-- hadoop fs -ls /home/mohit/Desktop/CloudComp/practical5/input -->


start-dfs.sh
start-yarn.sh

hadoop fs -mkdir -p /user/mohit
hadoop fs -mkdir -p /user/mohit/input
hadoop fs -ls /user/mohit/input
hadoop fs -put /home/mohit/Desktop/CloudComp/prac5_wordc/input/story.txt /user/mohit/input/
hadoop fs -rm -r /user/mohit/output


<!-- turn off safe mode -->
hdfs dfsadmin -safemode get
hdfs dfsadmin -safemode leave
hdfs fsck /

<!-- run the program -->
hadoop jar wc.jar WordCount /user/mohit/input/story.txt /user/mohit/output

<!-- output the result -->
hdfs dfs -ls /user/mohit/output
hdfs dfs -cat /user/mohit/output/part-r-00000