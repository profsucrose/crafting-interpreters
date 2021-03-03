package dev.profsucrose.tool;

import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.List;

// simple Java class that generates AST expression class boilerplate
public class GenerateAst {
    final static String OUTPUT_DIR = "src/main/java/dev/profsucrose/lox";
    final static String BASE_NAME = "Expr";

    public static void main(String[] args) throws Exception {
        defineAst(Arrays.asList(
            "Binary   : Expr left, Token operator, Expr right",
            "Grouping : Expr expression",
            "Literal  : Object value",
            "Unary    : Token operator, Expr right"
        ));
    }

    private static void defineAst(List<String> types) throws IOException {
        final String path = String.format("%s/%s.java", OUTPUT_DIR, BASE_NAME);
        final PrintWriter writer = new PrintWriter(path, StandardCharsets.UTF_8);

        writer.println("package dev.profsucrose.lox;");
        writer.println();
        writer.println("import java.util.List;");
        writer.println();
        writer.println("abstract class " + BASE_NAME + " {");

        defineVisitor(writer, types);

        for (final String type : types) {
            String className = type.split(":")[0].trim();
            String fields = type.split(":")[1].trim();
            defineType(writer, className, fields);
        }

        // base accept() method
        writer.println();
        writer.println("    abstract <R> R accept(Visitor<R> visitor);");

        writer.println("}");
        writer.close();
    }

    private static void defineVisitor(PrintWriter writer, List<String> types) {
        writer.println("    interface Visitor<R> {");

        for (String type : types) {
            String typeName = type.split(":")[0].trim();
            writer.println("        R visit" + typeName + BASE_NAME + "(" +
                typeName + " " + BASE_NAME.toLowerCase() + ");");
        }

        writer.println("    }");
    }

    private static void defineType(PrintWriter writer, String className, String fieldList) {
        writer.println("    static class " + className + " extends " + BASE_NAME + " {");

        // constructor
        writer.println("        " + className + "(" + fieldList + ") {");

        // store parameters in fields
        String[] fields = fieldList.split(", ");
        for (String field : fields) {
            String name = field.split(" ")[1];
            writer.println("            this." + name + " = " + name + ";");
        }

        writer.println("        }");

        // fields
        writer.println();
        for (String field : fields) {
            writer.println("        final " + field + ";");
        }

        // Visitor pattern
        writer.println();
        writer.println("        @Override");
        writer.println("        <R> R accept(Visitor<R> visitor) {");
        writer.println("            return visitor.visit" + className + BASE_NAME + "(this);");
        writer.println("        }");

        writer.println("    }");
    }
}
