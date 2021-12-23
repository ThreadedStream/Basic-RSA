#pragma once

#include <openssl/bn.h>
#include <iostream>
#include <functional>


namespace rsa
{
	typedef unsigned long long ull;
	typedef unsigned long ul;

	class RSA
	{
	public:

		//Implementing Builder pattern
		class RSABuilder
		{
			ull inner_p, inner_q, inner_e;

		public:
			RSABuilder& P(ull p)
			{
				inner_p = p;
				return *this;
			}

			RSABuilder& Q(ull q)
			{
				inner_q = q;
				return *this;
			}

			RSABuilder& E(ull e)
			{
				inner_e = e;
				return *this;
			}
			
			RSA create()
			{
				RSA instance(inner_p, inner_q, inner_e);
				return instance;
			}
		};

		int gcd(ull p, ull q);

		/*TODO: Deprecate in future. Only for testing purposes */
		inline void printSecretKey() noexcept 
		{
			std::cout << BN_get_word(d) <<'\n';
		}

		ull power(ull a, ull b, ull mod);

		void mod_inverse();

		/* Return value: encrypted message in form of cipher text */
		ull encrypt(ull message);
		/* Return value: decrypted cipher in form of a plain message */
		void decrypt(ull cipher);

		

	private:
		BIGNUM* e;
		BIGNUM* d;
		BIGNUM* p;
		BIGNUM* q;
		BIGNUM* n;

		
		RSA(ull p_f, ull q_f, ull e_f)
		{
			p = BN_new();
			e = BN_new();
			q = BN_new();
			n = BN_new();
			d = BN_new();
			BN_set_word(p, p_f);
			BN_set_word(q, q_f);
			BN_set_word(e, e_f);
			auto temp_n = p_f * q_f;

			BN_set_word(n, temp_n);
		}
		
	};


}
