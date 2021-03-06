/******************************************************************************
 * Copyright (c) <YEAR>, <OWNER>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FORANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are 
 * those of the authors and should not be interpreted as representing 
 * official policies either expressed or implied, of the FreeBSD Project.
 ******************************************************************************/

#include <iostream>
#include <json.h>
#include <validator.h>

/**
 * @brief JSON Schema is read from filee sample_schema.json
 */
void sample_1()
{
   Json::Value v;
   v["id"]      = 1;
   v["name"]    = "nithin";
   v["price"]   = 10.123;
   v["tags"][0] = "green";
   v["tags"][1] = "red";
   v["dimensions"]["length"] = 10;
   v["dimensions"]["width"] = 20;
   v["dimensions"]["height"] = 30;

   try {
      JsonValidator validator;
      validator.readSchema("sample_schema.json");
      int ret = validator.validate(&v); 
      if (0 == ret) {
         std::cout << "Sample-1: Valid JSON" << std::endl;
      } else {
         std::cout << "Sample-1: Invalid JSON" << std::endl;
      }
   } catch (Exception &e) {
      std::cout << e.what() << std::endl;
   }
}

/**
 * @brief JSON Schema is given as an input string.
 */
void sample_2()
{
   Json::Value schema;
   schema["type"] = "object";
   schema["properties"]["id"]["type"] = "integer";
   schema["properties"]["name"]["type"] = "string";
   schema["properties"]["price"]["type"]= "number";
   Json::Value tags;
   tags["type"] = "array";
   tags["items"]["type"] = "string";
   schema["properties"]["tags"] = tags;
   Json::Value dimensions;
   dimensions["type"] = "object";
   dimensions["properties"]["height"]["type"] = "number";
   dimensions["properties"]["width"]["type"] = "number";
   dimensions["properties"]["length"]["type"] = "number";
   schema["properties"]["dimensions"] = dimensions;

   Json::Value v;
   v["id"]      = 1;
   v["name"]    = "nithin";
   v["price"]   = 10.123;
   v["tags"][0] = "green";
   v["tags"][1] = "red";
   v["dimensions"]["length"] = 10;
   v["dimensions"]["width"] = 20;
   v["dimensions"]["height"] = 30;

   try {
      JsonValidator validator(&schema);
      int ret = validator.validate(&v); 
      if (0 == ret) {
         std::cout << "Sample-2: Valid JSON" << std::endl;
      } else {
         std::cout << "Sample-2: Invalid JSON" << std::endl;
      }
   } catch (Exception &e) {
      std::cout << e.what() << std::endl;
   }
}

/**
 * @brief The schema is given as Json::Value object
 */
void sample_3()
{
   std::string schema = "{\"type\" : \"string\"}";
   Json::Value v = "nithin";

   try {
      JsonValidator validator(schema);
      int ret = validator.validate(&v); 
      if (0 == ret) {
         std::cout << "Sample-3: Valid JSON" << std::endl;
      } else {
         std::cout << "Sample-3: Invalid JSON" << std::endl;
      }
   } catch (Exception &e) {
      std::cout << e.what() << std::endl;
   }
}

int main()
{
   sample_1();
   sample_2();
   sample_3();
   return 0;
}
