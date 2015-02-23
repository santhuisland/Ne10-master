/*
 *  Copyright 2013-15 ARM Limited and Contributors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of ARM Limited nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY ARM LIMITED AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL ARM LIMITED AND CONTRIBUTORS BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <unistd.h>
#include <android/log.h>
#include "NE10.h"

#define LOG_TAG    "DTL"
#define LOG(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#ifdef __cplusplus
extern "C"
{
#endif


void test_add1 (void)
{
    int i;
    ne10_float32_t thesrc[5];
    ne10_float32_t thesrc1[5];
    ne10_float32_t thedst[5];

    for (i = 0; i < 5; i++)
    {
        thesrc[i] = (ne10_float32_t) rand() / RAND_MAX * 5.0f;
        thesrc1[i] = (ne10_float32_t) rand() / RAND_MAX * 5.0f;
    }
   // thecst = 0.1f;//(ne10_float32_t) rand() / RAND_MAX * 5.0f;

    LOG("Testing thesrc = %f,%f,%f,%f,%f",thesrc[0],thesrc[1],thesrc[2],thesrc[3],thesrc[4]);
    LOG("Testing thesrc1 = %f,%f,%f,%f,%f",thesrc1[0],thesrc1[1],thesrc1[2],thesrc1[3],thesrc1[4]);

    ne10_add_float (thedst , thesrc, thesrc1, 5);
    LOG("Testing ne10_add_float_c = %f,%f,%f,%f,%f",thedst[0],thedst[1],thedst[2],thedst[3],thedst[4]);
}

/*
jint JNI_OnLoad(JavaVM *origJvm, void *reserved)
{
	LOG("JNI LOAD - begin");

	JNIEnv* env;
	if (origJvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
		LOG("JNI FAILED");
		return -1;
	}


	LOG("JNI LOAD - finished");
	//test_add1();

	return 0;
}

*/
jstring
Java_com_arm_ne10_demo_MainActivity_NE10RunTest(JNIEnv *env,
                                               jobject thiz)
{
    static int test_count = 0;
    sleep(3); // this is required for attaching debuger to process

    	int i=0;

    	i++;

    	LOG("Testing LIb");

    	ne10_result_t status;
    	LOG ("Going to initialze NE10...\n");

		status = ne10_init();
		LOG("Testing LIb 1");

		LOG("ne10_HasNEON = %d",ne10_HasNEON());
		LOG("Testing LIb 2");

		LOG("ne10_init_math = %d",ne10_init_math(1));

		LOG("Testing LIb 3");
		LOG("ne10_init_dsp = %d",ne10_init_dsp(1));

		LOG("Testing LIb 4");
		if (status != NE10_OK)
			LOG ("NE10 init failed.\n");

		LOG ("NE10 has been initialized.\n");
		test_add1();

    return env->NewStringUTF("hello");
    	//return NULL;
#if 0
    void (*test_funcs[])(void) = {test_abs, test_addc, test_add, test_divc,
                                  test_div, test_dot, test_len, test_mlac,
                                  test_mla, test_mulc, test_mul, test_normalize,
                                  test_rsbc, test_setc, test_subc, test_sub,
                                  test_addmat, test_detmat, test_identitymat,
                                  test_invmat, test_mulmat, test_mulcmatvec,
                                  test_submat, test_transmat,
                                  test_fir, test_fir_decimate,
                                  test_fir_interpolate, test_fir_lattice,
                                  test_fir_sparse, test_iir_lattice};

    while (test_count < (sizeof(test_funcs) / sizeof(void (*)(void)))) {
        /* ne10_log_buffer is a global buffer which contain test's result
         * ne10_log_buffer's position need be setup first
         */
        ne10_log_buffer_ptr = ne10_log_buffer;
        *ne10_log_buffer_ptr++ = '[';

        (*test_funcs[test_count])();
        ++test_count;

        /* ne10_log_buffer_ptr is updated in test_funcs */
        --ne10_log_buffer_ptr;
        *ne10_log_buffer_ptr = ']';

        return ((*env)->NewStringUTF(env, ne10_log_buffer));
    }
#endif
}

#ifdef __cplusplus
}
#endif
