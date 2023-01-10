package testing;

import edu.yu.pl.UDFParseTreeVisitor;
import edu.yu.pl.UserDefinedField;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestLanguage {
    // I am going to have one or two tests for each main thing I am adding

    // I first need to figure out how to even write a test for this
    // and his tests are buried in abstraction, so it is hard to tell
    // let's start with STR
    private final UDFParseTreeVisitor visitor;

    public TestLanguage() {
        visitor = new UDFParseTreeVisitor();
    }

    @Test
    public void testSTR() {
        UserDefinedField field0 = new UserDefinedField("STR(0)");
        visitor.setReferenceField("String0", field0);
        assertEquals("0", field0.evaluate(visitor));

        UserDefinedField field1 = new UserDefinedField("STR (11)");
        visitor.setReferenceField("String1", field1);
        assertEquals("11", field1.evaluate(visitor));
    }

    @Test
    public void testJOIN() {
        UserDefinedField join2 = new UserDefinedField("JOIN(-,'A','Tree')");
        visitor.setReferenceField("String0", join2);
        assertEquals("A-Tree", join2.evaluate(visitor));

        UserDefinedField join4 = new UserDefinedField("JOIN (/, 'I', 'am', STR(4), String0)");
        visitor.setReferenceField("String1", join4);
        assertEquals("I/am/4/A-Tree", join4.evaluate(visitor));
    }

    // for each of the boolean expressions, I will test once for <, ==, and > for num, plus one for String to show it works

    @Test
    public void testLess() {
        UserDefinedField less0 = new UserDefinedField("4 < 5");
        visitor.setReferenceField("String0", less0);
        assertEquals(true, less0.evaluate(visitor));

        UserDefinedField less1 = new UserDefinedField("5 < 5");
        visitor.setReferenceField("String1", less1);
        assertEquals(false, less1.evaluate(visitor));

        UserDefinedField less2 = new UserDefinedField("5 < 4");
        visitor.setReferenceField("String2", less2);
        assertEquals(false, less2.evaluate(visitor));

        UserDefinedField less3 = new UserDefinedField("'apple' < 'zeppelin'");
        visitor.setReferenceField("String3", less3);
        assertEquals(true, less3.evaluate(visitor));
    }

    @Test
    public void testLessEq() {
        UserDefinedField less0 = new UserDefinedField("4 <= 5");
        visitor.setReferenceField("String0", less0);
        assertEquals(true, less0.evaluate(visitor));

        UserDefinedField less1 = new UserDefinedField("5 <= 5");
        visitor.setReferenceField("String1", less1);
        assertEquals(true, less1.evaluate(visitor));

        UserDefinedField less2 = new UserDefinedField("5 <= 4");
        visitor.setReferenceField("String2", less2);
        assertEquals(false, less2.evaluate(visitor));

        UserDefinedField less3 = new UserDefinedField("'apple' <= 'zeppelin'");
        visitor.setReferenceField("String3", less3);
        assertEquals(true, less3.evaluate(visitor));
    }

    @Test
    public void testNotEq() {
        UserDefinedField less0 = new UserDefinedField("4 <> 5");
        visitor.setReferenceField("String0", less0);
        assertEquals(true, less0.evaluate(visitor));

        UserDefinedField less1 = new UserDefinedField("5 <> 5");
        visitor.setReferenceField("String1", less1);
        assertEquals(false, less1.evaluate(visitor));

        UserDefinedField less2 = new UserDefinedField("5 <> 4");
        visitor.setReferenceField("String2", less2);
        assertEquals(true, less2.evaluate(visitor));

        UserDefinedField less3 = new UserDefinedField("'apple' <> 'zeppelin'");
        visitor.setReferenceField("String3", less3);
        assertEquals(true, less3.evaluate(visitor));
    }

    @Test
    public void testGreatEq() {
        UserDefinedField less0 = new UserDefinedField("4 >= 5");
        visitor.setReferenceField("String0", less0);
        assertEquals(false, less0.evaluate(visitor));

        UserDefinedField less1 = new UserDefinedField("5 >= 5");
        visitor.setReferenceField("String1", less1);
        assertEquals(true, less1.evaluate(visitor));

        UserDefinedField less2 = new UserDefinedField("5 >= 4");
        visitor.setReferenceField("String2", less2);
        assertEquals(true, less2.evaluate(visitor));

        UserDefinedField less3 = new UserDefinedField("'apple' >= 'zeppelin'");
        visitor.setReferenceField("String3", less3);
        assertEquals(false, less3.evaluate(visitor));
    }

    @Test
    public void testGreater() {
        UserDefinedField less0 = new UserDefinedField("4 > 5");
        visitor.setReferenceField("String0", less0);
        assertEquals(false, less0.evaluate(visitor));

        UserDefinedField less1 = new UserDefinedField("5 > 5");
        visitor.setReferenceField("String1", less1);
        assertEquals(false, less1.evaluate(visitor));

        UserDefinedField less2 = new UserDefinedField("5 > 4");
        visitor.setReferenceField("String2", less2);
        assertEquals(true, less2.evaluate(visitor));

        UserDefinedField less3 = new UserDefinedField("'apple' > 'zeppelin'");
        visitor.setReferenceField("String3", less3);
        assertEquals(false, less3.evaluate(visitor));
    }

    @Test
    public void testEquals() {
        UserDefinedField less0 = new UserDefinedField("4 = 5");
        visitor.setReferenceField("String0", less0);
        assertEquals(false, less0.evaluate(visitor));

        UserDefinedField less1 = new UserDefinedField("5 = 5");
        visitor.setReferenceField("String1", less1);
        assertEquals(true, less1.evaluate(visitor));

        UserDefinedField less2 = new UserDefinedField("5 = 4");
        visitor.setReferenceField("String2", less2);
        assertEquals(false, less2.evaluate(visitor));

        UserDefinedField less3 = new UserDefinedField("'apple' = 'zeppelin'");
        visitor.setReferenceField("String3", less3);
        assertEquals(false, less3.evaluate(visitor));
    }

    @Test
    public void testAND() {
        UserDefinedField and0 = new UserDefinedField("TRUE AND false");
        visitor.setReferenceField("String0", and0);
        assertEquals(false, and0.evaluate(visitor));

        UserDefinedField and1 = new UserDefinedField("True AND 4 < 5");
        visitor.setReferenceField("String1", and1);
        assertEquals(true, and1.evaluate(visitor));
    }

    @Test
    public void testOR() {
        UserDefinedField or0 = new UserDefinedField("True OR False");
        visitor.setReferenceField("String0", or0);
        assertEquals(true, or0.evaluate(visitor));

        UserDefinedField or1 = new UserDefinedField("FALSE OR 3 > 5555555");
        visitor.setReferenceField("String1", or1);
        assertEquals(false, or1.evaluate(visitor));
    }

    /**
     Apparently, and takes priority over or
     False and false or true
     If and goes first, it is true, but if or goes first, it is false
     True or true and false, if or goes first, it is false, but if and goes first, it is true
     */
    @Test
    public void testANDBeforeOR() {
        UserDefinedField and0 = new UserDefinedField("False AND false OR true");
        visitor.setReferenceField("String0", and0);
        assertEquals(true, and0.evaluate(visitor));

        UserDefinedField and1 = new UserDefinedField("True OR true AND false");
        visitor.setReferenceField("String1", and1);
        assertEquals(true, and1.evaluate(visitor));
    }

    @Test
    public void testIN() {
        UserDefinedField in0 = new UserDefinedField("'cat' IN ('cat')");
        visitor.setReferenceField("String0", in0);
        assertEquals(true, in0.evaluate(visitor));

        UserDefinedField in1 = new UserDefinedField("'cat' IN ('cat', 'dog', 'mouse', 'cat', 'gerbil')");
        visitor.setReferenceField("String1", in1);
        assertEquals(true, in1.evaluate(visitor));

        UserDefinedField in2 = new UserDefinedField("'cat' IN ('cate', 'dog', 'mouse', 'Cat', 'gerbil')");
        visitor.setReferenceField("String1", in2);
        assertEquals(false, in2.evaluate(visitor));
    }

    @Test
    public void testNOT() {
        UserDefinedField not0 = new UserDefinedField("NOT(True)");
        visitor.setReferenceField("String0", not0);
        assertEquals(false, not0.evaluate(visitor));

        UserDefinedField not1 = new UserDefinedField("NOT ( 'cat' IN ('cate', 'dog', 'mouse', 'Cat', 'gerbil') )");
        visitor.setReferenceField("String1", not1);
        assertEquals(true, not1.evaluate(visitor));
    }

    @Test
    public void testIF() {
        UserDefinedField if0 = new UserDefinedField("IF (true, 'DUDE', STR(55.3))");
        visitor.setReferenceField("String0", if0);
        assertEquals("DUDE", if0.evaluate(visitor));

        UserDefinedField if1 = new UserDefinedField("IF ('cat' IN ('cate', 'dog', 'mouse', 'Cat', 'gerbil'), 'DUDE', STR(55.3) )");
        visitor.setReferenceField("String1", if1);
        assertEquals("55.3", if1.evaluate(visitor));
    }


}
