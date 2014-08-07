from distutils.core import setup, Extension

goalcoin_hash_module = Extension('goalcoin_hash',
                               sources = ['goalcoinmodule.c',
                                          'goalcoin.c',
                                          'sha3/blake.c',
                                          'sha3/groestl.c',
                                          'sha3/jh.c',
                                          'sha3/keccak.c',
                                          'sha3/skein.c',
                                          'sha3/whirlpool.c'],

                               include_dirs=['.', './sha3'])

setup (name = 'goalcoin_hash',
       version = '1.0',
       description = 'Bindings for proof of work used by GoalCoin',
       ext_modules = [goalcoin_hash_module])
