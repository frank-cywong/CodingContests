import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.Deque;
import java.util.ArrayDeque;
//import java.io.FileWriter;
//import java.io.IOException;

public class Database{
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int lines = Integer.parseInt(input.nextLine());
        StringBuilder codeBuilder = new StringBuilder();
        for (int i = 0; i < lines; i++) {
            String line = input.nextLine();
            codeBuilder.append(line).append("\n");
        }
        String code = codeBuilder.toString();

        System.out.print(format(code));
        //FileWriter out = new FileWriter("debug.output");
        //out.write(format(code));
        //out.close();
    }

    public static String format(String code) {
        StringBuilder result = new StringBuilder();
        Pattern regex = Pattern.compile("</?([a-zA-Z0-9]+)>");
        Matcher matcher = regex.matcher(code);
        Pattern regex2 = Pattern.compile("\\s+");
        
        Deque<String> tagStack = new ArrayDeque<String>();
        int start = 0;
        int indent = 0;
        while (start < code.length() && matcher.find(start)) {
            //System.out.println("FIND START:" + matcher.start());
            //System.out.println(code.substring(start, matcher.start()));
            //System.out.println(code.substring(matcher.start()));
            String tag = matcher.group(1);
            String content = code.substring(start, matcher.start());
            //System.out.println("TAG: " + tag);
            //System.out.println("CONTENT: " + content);
            //System.out.println("ALTCONTENT: " + code.substring(matcher.end()));
            if(tag.equals("br")){
              if(content.equals("") || content.equals("\n")){
                result.append("\t".repeat(indent)).append("<br>\n");
              } else {
                if(content.charAt(0) == '\n'){
                  content = content.substring(1);
                }
                Matcher matcher2 = regex2.matcher(content);
                content = matcher2.replaceAll(" ");
                //System.out.println(matcher2);
                result.append("\t".repeat(indent)).append(content).append(" <br>\n");
              }
            } else if (!content.equals("") && !content.equals("\n")) {
              if(content.charAt(0) == '\n'){
                content = content.substring(1);
              }
              Matcher matcher2 = regex2.matcher(content);
              content = matcher2.replaceAll(" ");
              //System.out.println(matcher2);
              result.append("\t".repeat(indent)).append(content).append("\n");
            }
            if (!matcher.group().contains("/")) {
                if(!tag.equals("br")){
                  result.append("\t".repeat(indent)).append(matcher.group()).append("\n");
                  if(!tag.equals("hr")){
                    tagStack.addFirst(tag);
                    if (!code.substring(matcher.end()).contains("</" + tag + ">")) {
                        return "SYNTAX ERROR";
                    }
                    indent++;
                  }
                }
            }
            else {
                if(tag.equals("br") || tag.equals("hr") || indent == 0){
                  return "SYNTAX ERROR";
                }
                //System.out.println("TAG STACK: " + tagStack);
                if(!tag.equals(tagStack.pollFirst())){
                  return "SYNTAX ERROR";
                }
                indent--;
                result.append("\t".repeat(indent)).append(matcher.group()).append("\n");
            }

            start = matcher.end();
        }
        if(indent != 0){
          return "SYNTAX ERROR";
        }
        //System.out.println(result);
        while(result.charAt(result.length() - 1) == '\n'){
          result.deleteCharAt(result.length() - 1);
        }
        result.append(code.substring(start));
        while(result.charAt(result.length() - 1) == '\n'){
          result.deleteCharAt(result.length() - 1);
        }
        return result.toString();
    }
}
