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

#include "xml.h"

void xml_init(xml_t *xml, char *buffer, unsigned short size) {
    thread_init(&xml->thread);
    xml->buffer = buffer;
    xml->capacity = size;
}

thread_state_t parse(xml_t *xml, char c) {
    xml->type = XML_NONE;

    thread_start(&xml->thread) {
        for (;;) {
            thread_wait(&xml->thread, c == '<');
            thread_yield(&xml->thread);
            
            if (c == '/') {
                thread_yield(&xml->thread);
                
                for (xml->size = 0;
                        xml->size < xml->capacity && c != ' ' && c != '>';
                        xml->size++) {
                    xml->buffer[xml->size] = c;
                    thread_yield(&xml->thread);
                }
                
                thread_wait(&xml->thread, c != ' ');
                xml->type = XML_CLOSE_ELEMENT;
            }
            else {
                for (xml->size = 0;
                        xml->size < xml->capacity
                            && c != ' ' && c != '/' && c != '>';
                        xml->size++) {
                    xml->buffer[xml->size] = c;
                    thread_yield(&xml->thread);
                }
                
                xml->type = XML_OPEN_ELEMENT;
            
                while (c == ' ') {
                    thread_wait(&xml->thread, c != ' ');
                    
                    if (c != '/' && c != '>') {
                        for (xml->size = 0;
                                xml->size < xml->capacity && c != '=';
                                xml->size++) {
                            xml->buffer[xml->size] = c;
                            thread_yield(&xml->thread);
                        }
                        
                        xml->type = XML_ATTRIBUTE;
                        
                        thread_assert(&xml->thread, c == '=');
                        thread_yield(&xml->thread);
                        thread_assert(&xml->thread, c == '"');
                        thread_yield(&xml->thread);
                        
                        for (xml->size = 0;
                                xml->size < xml->capacity && c != '"';
                                xml->size++) {
                            xml->buffer[xml->size] = c;
                            thread_yield(&xml->thread);
                        }
                        
                        xml->type = XML_VALUE;
                        thread_assert(&xml->thread, c == '"');
                        thread_yield(&xml->thread);
                    }
                }
                
                if (c == '/') {
                    thread_yield(&xml->thread);
                    xml->type = XML_CLOSE_ELEMENT;
                    xml->size = 0;
                }
            }
            
            thread_assert(&xml->thread, c == '>');
        }
    }

    return THREAD_STATE_FINISHED;
}

unsigned char xml_parse(xml_t *xml, char c) {
    parse(xml, c);
    return xml->type;
}

