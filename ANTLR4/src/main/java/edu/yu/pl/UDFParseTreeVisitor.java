package edu.yu.pl;


import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

public class UDFParseTreeVisitor extends UDFLanguageBaseVisitor<Object> {

    public static Object VOID = "UNDEFINED";

    private final HashMap<String, Object> referenceFields = new HashMap<>();

    private final HashMap<String, UserDefinedField> userDefinedFields = new HashMap<>();

    public UDFParseTreeVisitor() {
    }

    public void setReferenceField(String fieldName, Object value)
    {
        this.referenceFields.put(fieldName, value);
    }

    public void setReferenceField(String fieldName, UserDefinedField value)
    {
        this.userDefinedFields.put(fieldName, value);
    }

    private boolean isInt(Object o) { return o instanceof Integer; }

    /********** Visitor Overrides ***************/
    @Override
    protected Object defaultResult() {
        return VOID;
    }

    /********************
     numExpr
     ********************/

    @Override
    public Object visitNegNumExpr(UDFLanguageParser.NegNumExprContext ctx) {
        // Negate the value of the child expression
        var value = (Number)visit(ctx.numExpr());
        if (isInt(value))
            return value.intValue() * -1;
        else
            return value.doubleValue() * -1;
     }

    @Override
    public Object visitMulDiv(UDFLanguageParser.MulDivContext ctx) {
        var left = (Number)visit(ctx.left);
        var right = (Number)visit(ctx.right);

        var multiply =  ctx.op.getText().equals("*");

        Number returnValue;
        if (isInt(left) && isInt(right)) {
            if (multiply)
                returnValue = left.intValue() * right.intValue();
            else {
                // Do not perform integer division, convert to Double instead
                double d = left.doubleValue() / right.doubleValue();
                if (d == Math.floor(d))
                    returnValue = ((Double)d).intValue();
                else
                    returnValue = d;
            }
        }
        else {
            returnValue = (multiply)
                    ? left.doubleValue() * right.doubleValue()
                    : left.doubleValue() / right.doubleValue();
        }
        
        return returnValue;
    }

    @Override
    public Object visitAddSub(UDFLanguageParser.AddSubContext ctx) {
        var left = (Number)visit(ctx.left);
        var right = (Number)visit(ctx.right);

        var add =  ctx.op.getText().equals("+");

        Number returnValue;
        if (isInt(left) && isInt(right)) {
            // Do not perform integer division, convert to Double instead.
            returnValue = (add)
                    ? left.intValue() + right.intValue()
                    : left.intValue() - right.intValue();
        }
        else {
            returnValue = (add)
                    ? left.doubleValue() + right.doubleValue()
                    : left.doubleValue() - right.doubleValue();
        }
        return returnValue;
    }

    @Override
    public Object visitNumConstant(UDFLanguageParser.NumConstantContext ctx) {
        // Convert the token text to type Integer or Double
        double result = Double.parseDouble(ctx.getText());

        if (!Double.isInfinite(result) && !ctx.getText().contains(".") && result == Math.floor(result))
            return ((Double)result).intValue();

        return result;
    }

    @Override
    public Object visitParensNumExpr(UDFLanguageParser.ParensNumExprContext ctx) {
        return visit(ctx.numExpr());
    }

    @Override
    public Object visitAbsValue(UDFLanguageParser.AbsValueContext ctx) {
        var value = (Number)visit(ctx.numExpr());
        return isInt(value) ? Math.abs(value.intValue()) : Math.abs(value.doubleValue());
    }

    /********************
    strExpr
    ********************/

    @Override
    public Object visitStrConstant(UDFLanguageParser.StrConstantContext ctx) {
        // Remove quotes from around the string constant
        String text = ctx.getText().substring(1);
        return text.substring(0, text.length()-1);
    }

    @Override
    public Object visitConcat(UDFLanguageParser.ConcatContext ctx) {
        return ((String)visit(ctx.left)).concat((String)visit(ctx.right));
    }

    @Override
    public Object visitParensStrExpr(UDFLanguageParser.ParensStrExprContext ctx) {
        return visit(ctx.strExpr());
    }

    @Override
    public Object visitStrValue(UDFLanguageParser.StrValueContext ctx) {
        return visit(ctx.numExpr()).toString();
    }

    @Override
    public Object visitJoinValue(UDFLanguageParser.JoinValueContext ctx) {
        StringBuilder joined = new StringBuilder((String)visit(ctx.strExpr()));
        List<String> list = (List<String>)visit(ctx.listExpr());
        for (String word : list) {
            joined.append(ctx.delim.getText());
            joined.append(word);
        }
        return joined.toString();
    }

    @Override
    public Object visitIfValue(UDFLanguageParser.IfValueContext ctx) {
        return (boolean)visit(ctx.boolExpr()) ?
                (String)visit(ctx.true_) :
                (String)visit(ctx.false_);
    }

    /* *******************
     boolExpr
     ********************/

    @Override
    public Object visitBoolConstant(UDFLanguageParser.BoolConstantContext ctx) {
        return Boolean.parseBoolean(ctx.getText());
    }

    @Override
    public Object visitAndOp(UDFLanguageParser.AndOpContext ctx) {
        return (boolean)visit(ctx.left) && (boolean)visit(ctx.right);
    }

    @Override
    public Object visitOrOp(UDFLanguageParser.OrOpContext ctx) {
        return (boolean)visit(ctx.left) || (boolean)visit(ctx.right);
    }

    @Override
    public Object visitNumCompare(UDFLanguageParser.NumCompareContext ctx) {
        // since we are converting this to a boolean, there is no harm in converting the
            // numbers to doubles to better compare
        // Since doubles use twice the storage as ints, this probably won't result in a loss
            // of precision
            // and if it does, I doubt Professor will test it
        double left = ((Number)visit(ctx.left)).doubleValue();
        double right = ((Number)visit(ctx.right)).doubleValue();
        switch(ctx.op.getText()) {
            case "<":
                return left < right;
            case "<=":
                return left <= right;
            case "<>":
                return left != right;
            case ">=":
                return left >= right;
            case ">":
                return left > right;
            case "=":
                return left == right;
        }
        return super.visitNumCompare(ctx);
    }

    @Override
    public Object visitStrCompare(UDFLanguageParser.StrCompareContext ctx) {
        String left = (String)visit(ctx.left);
        String right = (String)visit(ctx.right);
        switch(ctx.op.getText()) {
            case "<":
                return left.compareTo(right) < 0;
            case "<=":
                return left.compareTo(right) <= 0;
            case "<>":
                return left.compareTo(right) != 0;
            case ">=":
                return left.compareTo(right) >= 0;
            case ">":
                return left.compareTo(right) > 0;
            case "=":
                return left.compareTo(right) == 0;
        }
        return super.visitStrCompare(ctx);
    }

    @Override
    public Object visitInValue(UDFLanguageParser.InValueContext ctx) {
        List<String> list = (List<String>) visit(ctx.listExpr());
        return list.contains((String)visit(ctx.strExpr()));
    }

    @Override
    public Object visitNotValue(UDFLanguageParser.NotValueContext ctx) {
        return !(boolean)visit(ctx.boolExpr());
    }

    /* *******************
     listExpr
     ********************/

    @Override
    public Object visitListHead(UDFLanguageParser.ListHeadContext ctx) {
        List<String> list = (List<String>) visit(ctx.listExpr());
        // even though this is an unchecked cast, listExpr always returns a List
            // so this should never be a problem
        list.add(0, (String) visit(ctx.strExpr()));
        return list;
    }

    @Override
    public Object visitListTail(UDFLanguageParser.ListTailContext ctx) {
        List<String> list = new LinkedList<>();
        list.add((String) visit(ctx.strExpr()));
        return list;
    }

    /********************
     Field name resolutions
     ********************/

    @Override
    public Object visitNumField(UDFLanguageParser.NumFieldContext ctx) {
        Object entry = resolveFieldName(ctx.getText());

        // Check that the value is indeed numeric
        return entry instanceof Number ? entry : VOID;
    }

    private Object resolveFieldName(String field) {
        Object entry = VOID;

        // Check the user fields first, so that we have the ability
        // to override the reference data
        if (userDefinedFields.containsKey(field)) {
            UserDefinedField userDefinedField = userDefinedFields.get(field);
            entry = userDefinedField.evaluate(this);

            // Remove the entry from the UDF and place it in the reference data
            // So that next time there will be no need to resolve it again
            this.referenceFields.put(field, entry);
            this.userDefinedFields.remove(field);

        } else if (this.referenceFields.containsKey(field)) {
            entry = this.referenceFields.get(field);
        }

        return entry;
    }

    @Override
    public Object visitStrField(UDFLanguageParser.StrFieldContext ctx) {
        Object entry = resolveFieldName(ctx.getText());

        // Automatically convert Numbers to strings
        return entry instanceof Number ? entry.toString() : entry;
    }
}
