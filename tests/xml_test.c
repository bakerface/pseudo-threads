/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013 Christopher M. Baker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "xml_test.h"
#include "xml.h"
#include <string.h>

void xml_test(jasmine_t *jasmine) {
    char buffer[10];
    xml_t xml;
    
    jasmine_describe(jasmine, "an xml") {
	    jasmine_before(jasmine) {
            xml_init(&xml, buffer, sizeof(buffer));
	    }

	    jasmine_after(jasmine) {
	        
	    }
	    
	    jasmine_it(jasmine, "should parse an open element") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, !strncmp("customer", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should ignore garbage before open elements") {
	        jasmine_expect(jasmine, xml_parse(&xml, 'a') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'd') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'f') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, !strncmp("customer", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should parse an attribute") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, 'i') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'd') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '=') == XML_ATTRIBUTE);
	        jasmine_expect(jasmine, !strncmp("id", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should parse a value") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, 'i') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'd') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '=') == XML_ATTRIBUTE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '0') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '0') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_VALUE);
	        jasmine_expect(jasmine, !strncmp("00", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should parse multiple attributes") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, 'i') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'd') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '=') == XML_ATTRIBUTE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '0') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '0') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_VALUE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'a') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'g') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '=') == XML_ATTRIBUTE);
	        jasmine_expect(jasmine, !strncmp("age", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should parse multiple values") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, 'i') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'd') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '=') == XML_ATTRIBUTE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '0') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '0') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_VALUE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'a') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'g') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '=') == XML_ATTRIBUTE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '3') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '2') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_VALUE);
	        jasmine_expect(jasmine, !strncmp("32", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should parse a close element") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '/') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_CLOSE_ELEMENT);
	        jasmine_expect(jasmine, !strncmp("customer", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should parse a close element with attributes") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, 'i') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'd') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '=') == XML_ATTRIBUTE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '0') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '0') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_VALUE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'a') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'g') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '=') == XML_ATTRIBUTE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '3') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '2') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_VALUE);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '/') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_CLOSE_ELEMENT);
	        jasmine_expect(jasmine, !strncmp("customer", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should parse a fast close element") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '/') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_CLOSE_ELEMENT);
	        jasmine_expect(jasmine, !strncmp("", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should parse a fast close with attributes") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, 'i') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'd') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '=') == XML_ATTRIBUTE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '0') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '0') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_VALUE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'a') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'g') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '=') == XML_ATTRIBUTE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '3') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '2') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '"') == XML_VALUE);
	        jasmine_expect(jasmine, xml_parse(&xml, '/') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_CLOSE_ELEMENT);
	        jasmine_expect(jasmine, !strncmp("", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should ignore whitespace before an open element") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '/') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_CLOSE_ELEMENT);
	        jasmine_expect(jasmine, !strncmp("customer", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should ignore whitespace before a fast close") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, '/') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_CLOSE_ELEMENT);
	        jasmine_expect(jasmine, !strncmp("", xml.buffer, xml.size));
	    }
	    
	    jasmine_it(jasmine, "should ignore whitespace before a close element") {
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_OPEN_ELEMENT);
	        jasmine_expect(jasmine, xml_parse(&xml, '<') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '/') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'c') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'u') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 's') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 't') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'o') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'm') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'e') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, 'r') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, ' ') == XML_NONE);
	        jasmine_expect(jasmine, xml_parse(&xml, '>') == XML_CLOSE_ELEMENT);
	        jasmine_expect(jasmine, !strncmp("customer", xml.buffer, xml.size));
	    }
    }
}

