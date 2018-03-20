//�����в�����{Args: filename}
/*
 * �㷨˼�룺����������ʽ����ƥ��
 * TextFile��̳���ArrayList,�����ȡ�ļ��������ļ���ÿһ����String�洢
 * ����ProduceFunction��������������ʽ��TextFile�е�ÿ��String����ƥ��
 * 
 * */
import java.util.regex.*;
import java.io.*;
import java.util.*;
public class ProduceFunction {

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		if(args.length<1){
			System.out.println("���ڵ���ʱ�����ļ���");
			System.exit(0);
		}
		//ȡ�����к�����
		Pattern p=Pattern.compile("\\s*\\w+\\s+\\w+\\s*\\([\\w\\s&\\*\\,\\[\\]]*\\)");
		//ע���еĺ����ų�����,
		Pattern q=Pattern.compile("^(//|/\\*|\\*)");
		System.out.println("Functions in "+args[0]+":");
		//�������ļ���ÿһ�н��е���
		int index=0;
		Matcher m=p.matcher("");//��Matcher����
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
			System.err.println("��д�ļ��쳣��"+e);
			throw new RuntimeException(e);
		}
		return sb.toString();
	}
}