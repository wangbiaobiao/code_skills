#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cson.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct subtest
{
    int id;
    char *test;
};

struct test
{
    char id;
    short num;
    int max;
    double value;
    char *name;
    struct subtest *sub;
    CsonList *list;
    char *str[2];
    CsonList *charList;
    CsonList *strList;
    char *subjson;
};

CsonModel subModel[] = 
{
    CSON_MODEL_OBJ(struct subtest),
    CSON_MODEL_INT(struct subtest, id),
    CSON_MODEL_STRING(struct subtest, test)
};


CsonModel model[] = 
{
    CSON_MODEL_OBJ(struct test),
    CSON_MODEL_CHAR(struct test, id),
    CSON_MODEL_SHORT(struct test, num),
    CSON_MODEL_INT(struct test, max),
    CSON_MODEL_DOUBLE(struct test, value),
    CSON_MODEL_STRING(struct test, name),
    CSON_MODEL_STRUCT(struct test, sub, subModel, sizeof(subModel)/sizeof(CsonModel)),
    CSON_MODEL_LIST(struct test, list, subModel, sizeof(subModel)/sizeof(CsonModel)),
    CSON_MODEL_ARRAY(struct test, str, CSON_TYPE_STRING, 2),
    CSON_MODEL_LIST(struct test, charList, CSON_MODEL_INT_LIST, CSON_BASIC_LIST_MODEL_SIZE),
    CSON_MODEL_LIST(struct test, strList, CSON_MODEL_STRING_LIST, CSON_BASIC_LIST_MODEL_SIZE),
    CSON_MODEL_JSON(struct test, subjson)
};

void csonTest(void)
{
    char *jsonStr = "{\"id\": 1, \"num\": 300, \"max\": 1000, \"value\": 10.3, \"name\": \"letter\", "
    "\"sub\": {\"id\": 20, \"test\": \"hello world\"},"
    " \"list\": [{\"id\": 21, \"test\": \"hello cson\"}, {\"id\": 22, \"test\": \"hello letter\"}],"
    "\"str\": [\"array1\", \"array2\"],"
    "\"charList\": [1, 12, 52], "
    "\"strList\": [\"str1\", \"str2\"],"
    "\"subjson\":{\"test\": \"hello\"}}";

    struct test *st = csonDecode(jsonStr, model, sizeof(model)/sizeof(CsonModel));
    printf("json 0x%08lx, id: %d, num: %d, max: %d, value: %f, name: %s\r\nsub: id: %d, test: %s\n",
        (unsigned long)st, st->id, st->num, st->max, st->value, st->name, st->sub ? st->sub->id : 0, st->sub ? st->sub->test : "null");
    printf("str: %s %s\n", st->str[0], st->str[1]);
    CsonList *p = st->list;
    while (p)
    {
        struct subtest *sst = p->obj;
        if (p->obj)
        {
            printf("list: id: %d, test: %s\n", sst->id, sst->test);
        }
        else
        {
            printf("list: null\n");
        }
        p = p->next;
    }
    p = st->charList;
    while (p)
    {
        long sst = (long)(p->obj);
        if (p->obj)
        {
            printf("list: long: %ld\n", sst);
        }
        p = p->next;
    }
    p = st->strList;
    while (p)
    {
        char *sst = p->obj;
        if (p->obj)
        {
            printf("list: str: %s\n", sst);
        }
        p = p->next;
    }
    printf("subjson: %s\n", st->subjson);

    char *root = csonEncode(st, model, sizeof(model)/sizeof(CsonModel), 512, 0);
    printf("encode: %s\n", root);

    csonFreeJson(root);
    csonFree(st, model, sizeof(model)/sizeof(CsonModel));
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
/** 项目结构体 */
struct project
{
    int id;
    char *name;
};

/** 仓库结构体 */
struct hub
{
    int id;
    char *user;
    struct project *cson;
};

/** 项目结构体数据模型 */
CsonModel projectModel[] = 
{
    CSON_MODEL_OBJ(struct project),
    CSON_MODEL_INT(struct project, id),
    CSON_MODEL_STRING(struct project, name),
};

/** 仓库结构体数据模型 */
CsonModel hubModel[] = 
{
    CSON_MODEL_OBJ(struct hub),
    CSON_MODEL_INT(struct hub, id),
    CSON_MODEL_STRING(struct hub, user),
    CSON_MODEL_STRUCT(struct hub, cson, projectModel, sizeof(projectModel)/sizeof(CsonModel))
};


void csonDemo(void)
{
    char *jsonDemo = "{\"id\": 1, \"user\": \"Letter\", \"cson\": {\"id\": 2, \"name\": \"cson\"}}";
    
    /** 解析json */
    struct hub *pHub = csonDecode(jsonDemo, hubModel, sizeof(hubModel)/sizeof(CsonModel));
    printf("hub: id: %d, user: %s, project id: %d, project name: %s\r\n",
        pHub->id, pHub->user, pHub->cson->id, pHub->cson->name);

    /** 序列化对象 */
    char *formatJson = csonEncode(pHub, hubModel, sizeof(hubModel)/sizeof(CsonModel), 512, 1);
    printf("format json: %s\r\n", formatJson);

    /** 释放结构体对象 */
    csonFree(pHub, hubModel, sizeof(hubModel)/sizeof(CsonModel));

    /** 释放序列化生成的json字符串 */
    csonFreeJson(formatJson);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    csonInit(malloc, free);
    csonDemo();
    printf("\n");
    csonTest();
    return 0;
}