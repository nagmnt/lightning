#ifndef LIGHTNING_DAEMON_BITCOIND_H
#define LIGHTNING_DAEMON_BITCOIND_H
#include "config.h"
#include <ccan/short_types/short_types.h>
#include <ccan/typesafe_cb/typesafe_cb.h>
#include <stdbool.h>

struct sha256_double;
struct lightningd_state;
struct ripemd160;
struct bitcoin_tx;
struct peer;
struct bitcoin_block;
/* -datadir arg for bitcoin-cli. */
extern char *bitcoin_datadir;

void bitcoind_estimate_fee_(struct lightningd_state *dstate,
			    void (*cb)(struct lightningd_state *dstate,
				       u64, void *),
			    void *arg);

#define bitcoind_estimate_fee(dstate, cb, arg)				\
	bitcoind_estimate_fee_((dstate),				\
			       typesafe_cb_preargs(void, void *, \
						   (cb), (arg),		\
						   struct lightningd_state *, \
						   u64),		\
			       (arg))

void bitcoind_send_tx(struct lightningd_state *dstate,
		      const struct bitcoin_tx *tx);

void bitcoind_get_chaintips_(struct lightningd_state *dstate,
			     void (*cb)(struct lightningd_state *dstate,
					struct sha256_double *blockids,
					void *arg),
			     void *arg);

#define bitcoind_get_chaintips(dstate, cb, arg)				\
	bitcoind_get_chaintips_((dstate),				\
				typesafe_cb_preargs(void, void *,	\
						    (cb), (arg),	\
						    struct lightningd_state *, \
						    struct sha256_double *), \
				(arg))

void bitcoind_getblockcount_(struct lightningd_state *dstate,
			     void (*cb)(struct lightningd_state *dstate,
					u32 blockcount,
					void *arg),
			     void *arg);

#define bitcoind_getblockcount(dstate, cb, arg)		\
	bitcoind_getblockcount_((dstate),				\
				typesafe_cb_preargs(void, void *,	\
						    (cb), (arg),	\
						    struct lightningd_state *, \
						    u32 blockcount),	\
				(arg))

void bitcoind_getblockhash_(struct lightningd_state *dstate,
			    u32 height,
			    void (*cb)(struct lightningd_state *dstate,
				       const struct sha256_double *blkid,
				       void *arg),
			    void *arg);
#define bitcoind_getblockhash(dstate, height, cb, arg)			\
	bitcoind_getblockhash_((dstate),				\
			       (height),				\
			       typesafe_cb_preargs(void, void *,	\
						   (cb), (arg),		\
						   struct lightningd_state *, \
						   const struct sha256_double *), \
			       (arg))

void bitcoind_getrawblock_(struct lightningd_state *dstate,
			   const struct sha256_double *blockid,
			   void (*cb)(struct lightningd_state *dstate,
				      struct bitcoin_block *blk,
				      void *arg),
			   void *arg);
#define bitcoind_getrawblock(dstate, blkid, cb, arg)			\
	bitcoind_getrawblock_((dstate), (blkid),			\
			      typesafe_cb_preargs(void, void *,		\
						  (cb), (arg),		\
						  struct lightningd_state *, \
						  struct bitcoin_block *), \
			      (arg))

void normalized_txid(const struct bitcoin_tx *tx, struct sha256_double *txid);

void check_bitcoind_config(struct lightningd_state *dstate);
#endif /* LIGHTNING_DAEMON_BITCOIND_H */
