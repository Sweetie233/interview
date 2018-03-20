//命令行参数：{Args: filename}
/*
 * 算法思想：利用正则表达式进行匹配
 * TextFile类继承自ArrayList,负责读取文件，并将文件中每一行以String存储
 * 主类ProduceFunction负责利用正则表达式对TextFile中的每个String进行匹配
 * 
 * */
import java.util.regex.*;
import java.io.*;
import java.util.*;
public class ProduceFunction {

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		if(args.length<1){
			System.out.println("请在调用时输入文件名");
			System.exit(0);
		}
		//取得所有函数名
		Pattern p=Pattern.compile("\\s*\\w+\\s+\\w+\\s*\\([\\w\\s&\\*\\,\\[\\]]*\\)");
		//注释中的函数排除在外,
		Pattern q=Pattern.compile("^(//|/\\*|\\*)");
		System.out.println("Functions in "+args[0]+":");
		//对输入文件的每一行进行迭代
		int index=0;
		Matcher m=p.matcher("");//空Matcher对象
		Matcher n=q.matcher("");
		for(String line:new TextFile(args[0])){
			m.reset(line);
			n.reset(line);
			//System.out.println(line);
			while(m.find() && !n.find())
				System.out.println(index++ +": "+m.group());
		}
		
	}

}
class TextFile extends ArrayList<String>{
	public TextFile(String filename){
		super(Arrays.asList(read(filename).split("\n")));
		if(get(0).equals(""))
			remove(0);
	}
	
	public static String read(String filename){
		StringBuilder sb=new StringBuilder();
		try{
			BufferedReader in=new BufferedReader(new FileReader(
				new File(filename).getAbsoluteFile()));
			try{
				String s;
				while((s=in.readLine())!=null){
					sb.append(s);
					sb.append("\n");
				}
			}finally{
				in.close();
			}
		}catch(IOException e){
			System.err.println("读写文件异常："+e);
			throw new RuntimeException(e);
		}
		return sb.toString();
	}
}