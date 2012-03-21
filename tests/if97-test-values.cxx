/* libh2o -- water & steam properties
 * (c) 2012 Michał Górny
 * Released under the terms of the 2-clause BSD license
 */

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#include "h2o"

#include <cmath>
#include <cstdio>

int exit_status;

void _check(double result, double expected, double precision, const char* call,
		const char* arg1, double arg1_val,
		const char* arg2, double arg2_val)
{
	double difference = std::fabs(expected - result);

	if (difference >= precision)
	{
		std::fprintf(stderr, "[FAIL] %s(%s=%.3e, %s=%.3e) = %.9e, while %.9e expected.\n",
				call, arg1, arg1_val, arg2, arg2_val,
				result, expected);
		exit_status++;
	}
	else
		std::fprintf(stderr, "[ OK ] %s(%s=%.3e, %s=%.3e) = %.9e.\n",
				call, arg1, arg1_val, arg2, arg2_val,
				result);
}

void _check_vuhs(h2o::H2O* obj,
		double v_expected, double v_precision,
		double u_expected, double u_precision,
		double h_expected, double h_precision,
		double s_expected, double s_precision,
		const char* arg1, double arg1_val,
		const char* arg2, double arg2_val)
{
	_check(obj->v(), v_expected, v_precision, "v",
			arg1, arg1_val, arg2, arg2_val);
	_check(obj->u(), u_expected, u_precision, "u",
			arg1, arg1_val, arg2, arg2_val);
	_check(obj->h(), h_expected, h_precision, "h",
			arg1, arg1_val, arg2, arg2_val);
	_check(obj->s(), s_expected, s_precision, "s",
			arg1, arg1_val, arg2, arg2_val);

	delete obj;
}

int main(void)
{
	_check_vuhs(new h2o::H2O(3., 300),
			0.100215168E-2, 1E-11,
			0.112324818E+3, 1E-6,
			0.115331273E+3, 1E-6,
			0.392294792E+0, 1E-9,
			"p", 3., "T", 300);
	_check_vuhs(new h2o::H2O(80, 300),
			0.971180894E-3, 1E-12,
			0.106448356E+3, 1E-6,
			0.184142828E+3, 1E-6,
			0.368563852E+0, 1E-9,
			"p", 80, "T", 300);
	_check_vuhs(new h2o::H2O(3., 500),
			0.120241800E-2, 1E-11,
			0.971934985E+3, 1E-6,
			0.975542239E+3, 1E-6,
			0.258041912E+1, 1E-8,
			"p", 3., "T", 500);

	_check_vuhs(new h2o::H2O(35E-4, 300),
			0.394913866E+2, 1E-6,
			0.241169160E+4, 1E-4,
			0.254991145E+4, 1E-4,
			0.852238967E+1, 1E-5,
			"p", 35E-4, "T", 300);
	_check_vuhs(new h2o::H2O(35E-4, 700),
			0.923015898E+2, 1E-6,
			0.301262819E+4, 1E-4,
			0.333568375E+4, 1E-4,
			0.101749996E+2, 1E-6,
			"p", 35E-4, "T", 700);
	_check_vuhs(new h2o::H2O(30E+0, 700),
			0.542946619E-2, 1E-10,
			0.246861076E+4, 1E-4,
			0.263149474E+4, 1E-4,
			0.517540298E+1, 1E-5,
			"p", 30E+0, "T", 700);

	return exit_status;
}
