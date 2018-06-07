

import junit.framework.TestCase;
import org.junit.Rule;
import org.junit.rules.ErrorCollector;

import static org.hamcrest.core.IsEqual.equalTo;


//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {
    @Rule
    public ErrorCollector collector = new ErrorCollector();

    public UrlValidatorTest(String testName) {
        super(testName);
    }



    public void testManualTest() {
//You can use this function to implement your manual testing
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println("Testing Manually: ");
        urlparts createdURL = new urlparts("", true); // default value true, will set false inside logic
        for (urlparts i:scheme) {
            for (urlparts j:authority) {
                for (urlparts k:port) {
                    for (urlparts l:path) {
                        for (urlparts m:query) {
                            // Non-optional parts
                            if (!i.value || !j.value) {
                                createdURL.value = false;
                            }
                            // optional url parts
                            else {
                                if (!l.value || !m.value || !k.value) {
                                    createdURL.value = false;
                                }
                            }
                            createdURL.part = i.part + j.part + k.part + l.part + m.part;
                            try {
                                if (createdURL.value) {
                                    assertTrue(urlVal.isValid(createdURL.part));
                                } else {
                                    assertFalse(urlVal.isValid(createdURL.part));
                                }
                            } catch (Throwable t) {
                                System.out.println(createdURL.part + " failed");

                            }
                        }
                    }
                }
            }
        }





    }

    // First partition will be valid URLs
    public void testYourFirstPartition() {
        //You can use this function to implement your First Partition testing

    }
    // second partition will be invalid URLs
    public void testYourSecondPartition() {
        //You can use this function to implement your Second Partition testing

    }
    //You need to create more test cases for your Partitions if you need to

    public void testIsValid() {
        //You can use this function for programming based testing

    }


    public static void main(String[] argv) {

        UrlValidatorTest fct = new UrlValidatorTest("url test");
        fct.testManualTest();
    }

    urlparts[] scheme = {
            new urlparts("https://", true),
            new urlparts("u6p:/", false)
    };
    urlparts[] authority = {
            new urlparts("www.google.com", true),
            new urlparts("www.c", false)
    };
    urlparts[] port = {
            new urlparts("", true),
            new urlparts(":80", true),
            new urlparts(":-2", false)
    };
    urlparts[] path = {
            new urlparts("", true),
            new urlparts("/", true),
            new urlparts("/#/", false)
    };
    urlparts[] query = {
            new urlparts("?Hello=new", true)
    };
}