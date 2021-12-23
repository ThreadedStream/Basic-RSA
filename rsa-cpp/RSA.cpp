#include "RSA.h"

#pragma comment(lib, "libcrypto.lib")


/* Credit to https://www.quora.com/Why-do-pow-function-is-not-working-for-large-range-of-value */
rsa::ull rsa::RSA::power(ull a, ull b, ull mod)
{
	ull answer = 1ULL;

	while (b)
	{
		if (b & 1)
			answer = (answer * a) % mod;
		a = (a * a) % mod;
		b /= 2;
	}
	return answer;
}

rsa::ull rsa::RSA::encrypt(ull message)
{
	rsa::ull mod = BN_get_word(n);

	ull c = power(message, BN_get_word(e), mod);

	return c;
}

void rsa::RSA::decrypt(ull cipher)
{
	ull mod = BN_get_word(n);


	std::cout << "Decrypting...\n";
	ull message = power(cipher, BN_get_word(d), mod);
	std::cout << "Decryption process has finished successfully! The message is" << message << '\n';
}


int rsa::RSA::gcd(ull a, ull b)
{
	if (a % b == 0)
	{
		return b;
	}

	else
	{
		return gcd(b, a % b);
	}
}

void rsa::RSA::mod_inverse()
{


	/* Camichael's totient function */
	auto phi = [&]()->ull
	{
		auto temp_p = BN_get_word(p);
		auto temp_q = BN_get_word(q);
		
		ull lcm = std::abs(static_cast<long long>(temp_p - 1) *
			static_cast<long long>(temp_q - 1)) /	gcd(temp_p - 1, temp_q - 1);

		return lcm;
	};

	ull res = phi();
	auto mod = BN_new();
	BN_set_word(mod, res);
	BN_CTX* ctx = BN_CTX_new();
	BN_mod_inverse(d, e, mod, ctx);
}