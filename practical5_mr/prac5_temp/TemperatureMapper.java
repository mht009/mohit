import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;


public class TemperatureMapper
  extends Mapper<LongWritable, Text, Text, IntWritable>
{
  private static final int MISSING = 9999;
  
  public void map(LongWritable key, Text value, Mapper<LongWritable, Text, Text, IntWritable>.Context context) throws IOException, InterruptedException {
    int airTemperature;
    String line = value.toString();
    String sensor = line.substring(0, 4);
    
    if (line.charAt(87) == '+') {
      airTemperature = Integer.parseInt(line.substring(88, 92));
    } else {
      airTemperature = Integer.parseInt(line.substring(87, 92));
    } 
    String quality = line.substring(92, 93);
    if (airTemperature != 9999 && quality.matches("[01459]"))
      context.write(new Text(sensor), new IntWritable(airTemperature)); 
  }
}