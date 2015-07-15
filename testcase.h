/* 
 * File:   testcase.h
 * Author: kobe
 *
 * Created on 2014年12月2日, 下午 2:29
 */

#ifndef TESTCASE_H
#define	TESTCASE_H

#ifdef	__cplusplus
extern "C" {
#endif

void Script_Test(void);
USHORT ShowActionMessage(STR * title,ezxml_t Action);
void ReadTestCase(ezxml_t TestCase);
USHORT ShowTestCaseNodeInfo(STR * title,ezxml_t NODE);
USHORT ShowTestCase(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TESTCASE_H */

