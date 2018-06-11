

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
        System.out.println(urlVal.isValid("http://www.google.com/hello/"));
    }


    public void testScheme() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        urlparts createdURL = new urlparts("", true); // default value true, will set false inside logic
        System.out.println("Testing Schemes:");
        for (urlparts scheme:scheme) {
            if (!scheme.value) {
                createdURL.value = false;
            } else {
                createdURL.value = true;
            }
            createdURL.part = scheme.part + authority[0].part + port[0].part + path[0].part + query[0].part;
            try {
                if (createdURL.value) {
                    assertTrue(urlVal.isValid(createdURL.part));
                } else {
                    assertFalse(urlVal.isValid(createdURL.part));
                }
            } catch (Throwable t) {
                System.out.println("===== assertion failed =====\n" + createdURL.part);
                System.out.println("Expected: " + createdURL.value);
                System.out.println("Result: " + !createdURL.value);
                System.out.println("Input: scheme: " + scheme.value + " | authority: " + authority[0].value + " | port: " + port[0].value + " | path: " + path[0].value + " | query: " + query[0].value + "\n");
            }
        }


    }

    public void testAuthority() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        urlparts createdURL = new urlparts("", true); // default value true, will set false inside logic
        System.out.println("Testing Authorities:");
        for (urlparts authority:authority) {
            if (!authority.value) {
                createdURL.value = false;
            } else {
                createdURL.value = true;
            }
            createdURL.part = scheme[0].part + authority.part + port[0].part + path[0].part + query[0].part;
            try {
                if (createdURL.value) {
                    assertTrue(urlVal.isValid(createdURL.part));
                } else {
                    assertFalse(urlVal.isValid(createdURL.part));
                }
            } catch (Throwable t) {
                System.out.println("===== assertion failed =====\n" + createdURL.part);
                System.out.println("Expected: " + createdURL.value);
                System.out.println("Result: " + !createdURL.value);
                System.out.println("Input: scheme: " + scheme[0].value + " | authority: " + authority.value + " | port: " + port[0].value + " | path: " + path[0].value + " | query: " + query[0].value + "\n");
            }
        }

    }

    public void testPort(){
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        urlparts createdURL = new urlparts("", true); // default value true, will set false inside logic
        System.out.println("Testing Ports:");
        for (urlparts port:port) {
            if (!port.value) {
                createdURL.value = false;
            } else {
                createdURL.value = true;
            }
            createdURL.part = scheme[0].part + authority[0].part + port.part + path[0].part + query[0].part;
            try {
                if (createdURL.value) {
                    assertTrue(urlVal.isValid(createdURL.part));
                } else {
                    assertFalse(urlVal.isValid(createdURL.part));
                }
            } catch (Throwable t) {
                System.out.println("===== assertion failed =====\n" + createdURL.part);
                System.out.println("Expected: " + createdURL.value);
                System.out.println("Result: " + !createdURL.value);
                System.out.println("Input: scheme: " + scheme[0].value + " | authority: " + authority[0].value + " | port: " + port.value + " | path: " + path[0].value + " | query: " + query[0].value + "\n");
            }
        }
    }

    public void testPath() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        urlparts createdURL = new urlparts("", true); // default value true, will set false inside logic
        System.out.println("Testing Paths:");
        for (urlparts path:path) {
            if (!path.value) {
                createdURL.value = false;
            } else {
                createdURL.value = true;
            }
            createdURL.part = scheme[0].part + authority[0].part + port[0].part + path.part + query[0].part;
            try {
                if (createdURL.value) {
                    assertTrue(urlVal.isValid(createdURL.part));
                } else {
                    assertFalse(urlVal.isValid(createdURL.part));
                }
            } catch (Throwable t) {
                System.out.println("===== assertion failed =====\n" + createdURL.part);
                System.out.println("Expected: " + createdURL.value);
                System.out.println("Result: " + !createdURL.value);
                System.out.println("Input: scheme: " + scheme[0].value + " | authority: " + authority[0].value + " | port: " + port[0].value + " | path: " + path.value + " | query: " + query[0].value + "\n");
            }
        }
    }

    public void testQuery() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        urlparts createdURL = new urlparts("", true); // default value true, will set false inside logic
        System.out.println("Testing Queries:");
        for (urlparts query:query) {
            if (!query.value) {
                createdURL.value = false;
            } else {
                createdURL.value = true;
            }
            createdURL.part = scheme[0].part + authority[0].part + port[0].part + path[0].part + query.part;
            try {
                if (createdURL.value) {
                    assertTrue(urlVal.isValid(createdURL.part));
                } else {
                    assertFalse(urlVal.isValid(createdURL.part));
                }
            } catch (Throwable t) {
                System.out.println("===== assertion failed =====\n" + createdURL.part);
                System.out.println("Expected: " + createdURL.value);
                System.out.println("Result: " + !createdURL.value);
                System.out.println("Input: scheme: " + scheme[0].value + " | authority: " + authority[0].value + " | port: " + port[0].value + " | path: " + path[0].value + " | query: " + query.value + "\n");
            }
        }
    }


    public void testIsValid() {
        //You can use this function for programming based testing
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        urlparts createdURL = new urlparts("", true); // default value true, will set false inside logic
        for (urlparts scheme:scheme) {
            for (urlparts authority:authority) {
                for (urlparts port:port) {
                    for (urlparts path:path) {
                        for (urlparts query:query) {
                            // Non-optional parts
                            if (!scheme.value || !authority.value) {
                                createdURL.value = false;
                            }
                            // optional url parts
                            else {
                                createdURL.value = true;
                                if (!port.value || !path.value || !query.value) {
                                    createdURL.value = false;
                                } else {
                                    createdURL.value = true;
                                }
                            }
                            createdURL.part = scheme.part + authority.part + port.part + path.part + query.part;
                            try {
                                if (createdURL.value) {
                                    assertTrue(urlVal.isValid(createdURL.part));
                                } else {
                                    assertFalse(urlVal.isValid(createdURL.part));
                                }
                            } catch (Throwable t) {
                                System.out.println(createdURL.part + " assertion failed");
                                System.out.println("Expected: " + createdURL.value);
                                System.out.println("Result: " + !createdURL.value);
                                System.out.println("Input: scheme: " + scheme.value + " | authority: " + authority.value + " | port: " + port.value + " | path: " + path.value + " | query: " + query.value + "\n");
                            }
                        }
                    }
                }
            }
        }


    }


    public static void main(String[] argv) {

        UrlValidatorTest fct = new UrlValidatorTest("url test");
        fct.testManualTest();
        //fct.testIsValid();
        fct.testScheme();
        fct.testAuthority();
        fct.testPort();
        fct.testPath();
        fct.testQuery();
    }

    urlparts[] scheme = {
            new urlparts("http://", true),
            new urlparts("https://", true),
            new urlparts("u6p:/", false)
    };
    urlparts[] authority = {
            new urlparts("www.google.com", true),
            new urlparts("~!@@2@.", false)
    };
    urlparts[] port = {
            new urlparts("", true),
            new urlparts(":80", true),
            new urlparts(":-2", false)
    };
    urlparts[] path = {
            new urlparts("", true),
            new urlparts("/hello/", true),
            new urlparts("/]", false)
    };
    urlparts[] query = {
            new urlparts("", true),
            new urlparts("?Hello=new", true)
    };
}