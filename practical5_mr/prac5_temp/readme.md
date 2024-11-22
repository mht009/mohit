javac -classpath ${HADOOP_HOME}/hadoop-core-1.2.1.jar -d weather_classes TemperatureMapper.java MinTemperatureReducer.java MinTemperature.java
jar -cvf mintemperature-sensor.jar -C weather_classes/ .
<!-- hadoop fs -ls /home/mohit/Desktop/CloudComp/practical5/input -->


start-dfs.sh
start-yarn.sh

hadoop fs -mkdir -p /user/mohit
hadoop fs -mkdir -p /user/mohit/input
hadoop fs -put /home/mohit/Desktop/CloudComp/prac5_temp/input/dataset.txt /user/mohit/input/

<!-- turn off safe mode -->
hdfs dfsadmin -safemode get
hdfs dfsadmin -safemode leave
hdfs fsck /


hadoop jar /home/mohit/Desktop/CloudComp/prac5_temp/mintemperature-sensor.jar MinTemperature /user/mohit/input /user/mohit/output

hdfs dfs -ls /user/mohit/output
hdfs dfs -cat /user/mohit/output/part-r-00000



hadoop fs -rm -r /user/mohit/output




******************************************************************************************************************************************************
Since you’re using Java 17, and Hadoop is not fully compatible with this version, it’s causing issues with starting the ResourceManager due to module system restrictions.

### Suggested Steps

#### 1. **Downgrade Java Version**

Hadoop 3.x is generally compatible with Java 8, and running Hadoop on Java 8 should resolve the compatibility issues. Here’s how to install and switch to Java 8:

1. **Install Java 8**:

   ```bash
   sudo apt-get update
   sudo apt-get install openjdk-8-jdk
   ```

2. **Switch to Java 8**:

   Update the alternatives to point to Java 8:

   ```bash
   sudo update-alternatives --config java
   sudo update-alternatives --config javac
   ```

   Choose the Java 8 option from the list.

3. **Verify Java Version**:

   Ensure Java 8 is now the default:

   ```bash
   java -version
   ```

   You should see Java 8 as the active version.

4. **Restart Hadoop Services**:

   After switching Java versions, restart Hadoop services:

   ```bash
   stop-yarn.sh
   stop-dfs.sh
   start-dfs.sh
   start-yarn.sh
   ```

#### 2. **Verify Configuration Files**

Ensure the `yarn-site.xml` configuration is correct. It should not contain `localhost:8032:8032` as shown in the error message. Verify that the addresses and ports are correctly specified:

```xml
<configuration>
    <property>
        <name>yarn.resourcemanager.hostname</name>
        <value>localhost</value>
    </property>
    <property>
        <name>yarn.resourcemanager.scheduler.address</name>
        <value>localhost:8030</value>
    </property>
    <property>
        <name>yarn.resourcemanager.resource-tracker.address</name>
        <value>localhost:8025</value>
    </property>
    <property>
        <name>yarn.resourcemanager.admin.address</name>
        <value>localhost:8141</value>
    </property>
    <property>
        <name>yarn.resourcemanager.webapp.address</name>
        <value>localhost:8088</value>
    </property>
</configuration>
```

#### 3. **Check Hadoop Logs**

After making these changes, monitor the logs to ensure that the services start correctly and that there are no further errors:

```bash
tail -f /usr/local/hadoop/logs/yarn--resourcemanager-*.log
```

#### 4. **Reconfigure Environment Variables**

Ensure that your Hadoop environment variables are set correctly, especially `JAVA_HOME`:

```bash
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
```

Add this to your `.bashrc` or `.profile` and reload it:

```bash
source ~/.bashrc
```

### Summary

1. **Install Java 8** and switch to it.
2. **Update `yarn-site.xml`** to ensure proper configuration.
3. **Restart Hadoop services** and monitor logs.

If you follow these steps, it should resolve the issues with starting the ResourceManager. If problems persist, reviewing detailed logs and configuration settings will be essential.

Great, you've successfully switched to Java 8. Now, let's ensure Hadoop is properly configured and running with the correct Java version.

### Next Steps

#### 1. **Verify Hadoop Configuration**

Ensure that the Hadoop configuration files are pointing to the correct Java version. Verify `hadoop-env.sh` and `yarn-site.xml`:

**`hadoop-env.sh`**:

1. **Open `hadoop-env.sh`**:

   ```bash
   nano $HADOOP_CONF_DIR/hadoop-env.sh
   ```

2. **Set the Java Home Path**:

   Ensure `JAVA_HOME` is set to the Java 8 installation directory:

   ```bash
   export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
   ```

3. **Save and Exit**:

   Press `Ctrl + X`, then `Y`, and `Enter`.

**`yarn-site.xml`**:

Verify that `yarn-site.xml` does not have any invalid configurations. It should not have `localhost:8032:8032` as an address.

```xml
<configuration>
    <property>
        <name>yarn.resourcemanager.hostname</name>
        <value>localhost</value>
    </property>
    <property>
        <name>yarn.resourcemanager.scheduler.address</name>
        <value>localhost:8030</value>
    </property>
    <property>
        <name>yarn.resourcemanager.resource-tracker.address</name>
        <value>localhost:8025</value>
    </property>
    <property>
        <name>yarn.resourcemanager.admin.address</name>
        <value>localhost:8141</value>
    </property>
    <property>
        <name>yarn.resourcemanager.webapp.address</name>
        <value>localhost:8088</value>
    </property>
</configuration>
```

#### 2. **Restart Hadoop Services**

1. **Stop Hadoop Services**:

   ```bash
   stop-yarn.sh
   stop-dfs.sh
   ```

2. **Start Hadoop Services**:

   ```bash
   start-dfs.sh
   start-yarn.sh
   ```

3. **Check Service Status**:

   Confirm that services are running:

   ```bash
   jps
   ```

   You should see `NameNode`, `DataNode`, `ResourceManager`, and `NodeManager`.

4. **Monitor Logs**:

   Check logs for any errors:

   ```bash
   tail -f /usr/local/hadoop/logs/yarn--resourcemanager-*.log
   ```

#### 3. **Check Network Ports**

Verify that the necessary ports are listening. For `ResourceManager`, port 8032 should be open:

```bash
netstat -an | grep 8032
```

If the port is still not listening, ensure no other services are conflicting and that the firewall rules allow communication on these ports.

#### 4. **Test Hadoop Functionality**

Run a basic Hadoop command to ensure everything is working:

```bash
hadoop fs -ls /
```

This should list the root directory of HDFS. If this works, try running a simple MapReduce job to verify the complete setup.

### Summary

1. **Ensure `hadoop-env.sh` and `yarn-site.xml` are configured correctly**.
2. **Restart Hadoop services** and verify their status.
3. **Check network ports** and ensure there are no conflicts.
4. **Test Hadoop commands** to ensure functionality.

Following these steps should help you get Hadoop up and running with Java 8. If you encounter any further issues, provide the logs or error messages for more detailed troubleshooting.