import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class MinTemperature {
  public static void main(String[] args) throws Exception {
    if (args.length != 2) {
      System.err.println("Usage: MinTemperature <input path> <output path>");
      System.exit(-1);
    } 
    
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "min temprature");
    job.setJarByClass(MinTemperature.class);
    job.setJobName("Min temperature");
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
    job.setMapperClass(TemperatureMapper.class);
    job.setReducerClass(MinTemperatureReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}

// javac -classpath ${HADOOP_HOME}/hadoop-core-1.2.1.jar -d weather_classes TemperatureMapper.java MinTemperatureReducer.java MinTemperature.java
