#ifndef __bbs__plus__included__
#define __bbs__plus__included__

#include <stdint.h>

/* Used for receiving a ByteBuffer from C that was allocated by either C or Rust.
*  If Rust allocated, then the outgoing struct is `ffi_support::ByteBuffer`
*  Caller is responsible for calling free where applicable.
*/
struct ByteBuffer {
    int64_t len;
    uint8_t *data;
};

struct ExternError {
    int32_t code;
    char* message; /* note: nullable */
};

typedef enum {
    Revealed = 1,
    HiddenProofSpecificBlinding = 2,
    HiddenExternalBlinding = 3,
} proof_message_t;

typedef enum {
    /* The proof verified */
    Success = 200;
    /* The proof failed because the signature proof of knowledge failed */
    BadSignature = 400,
    /* The proof failed because a hidden message was invalid when the proof was created */
    BadHiddenMessage = 401,
    /* The proof failed because a revealed message was invalid */
    BadRevealedMessage = 402,
} signature_proof_status;

#ifdef __cplusplus
extern "C" {
#endif

void bbs_string_free(char* string);
void bbs_byte_buffer_free(struct ByteBuffer data);

int32_t bbs_verify_context_add_message_bytes(uint64_t handle,
                                             const struct ByteBuffer *message const,
                                             struct ExternError *err);

int32_t bbs_verify_context_add_message_prehashed(uint64_t handle,
                                                 const struct ByteBuffer *message const,
                                                 struct ExternError *err);

int32_t bbs_verify_context_set_public_key(uint64_t handle,
                                          const struct ByteBuffer *public_key const,
                                          struct ExternError *err);

int32_t bbs_verify_context_set_public_key(uint64_t handle,
                                          const struct ByteBuffer *public_key const,
                                          struct ExternError *err);

uint64_t bbs_blind_commitment_context_init(struct ExternError *err);

int32_t bbs_blind_commitment_context_finish(uint64_t handle,
                                            struct ByteBuffer *out_context,
                                            struct ByteBuffer *blinding_factor,
                                            struct ExternError *err);

int32_t bbs_blind_commitment_context_add_message_string(uint64_t handle,
                                                        const char *message const,
                                                        struct ExternError *err);

int32_t bbs_blind_commitment_context_add_message_bytes(uint64_t handle,
                                                       const struct ByteBuffer *message const,
                                                       struct ExternError *err);

int32_t bbs_blind_commitment_context_add_message_prehashed(uint64_t handle,
                                                           const struct ByteBuffer *message const,
                                                           struct ExternError *err);

int32_t bbs_blind_commitment_context_set_public_key(uint64_t handle,
                                                    const struct ByteBuffer* public_key const,
                                                    struct ExternError *err);

int32_t bbs_blind_commitment_context_set_nonce_string(uint64_t handle,
                                                      const char *message const,
                                                      struct ExternError *err);

int32_t bbs_blind_commitment_context_set_nonce_bytes(uint64_t handle,
                                                     const struct ByteBuffer *message const,
                                                     struct ExternError *err);

int32_t bbs_blind_commitment_context_set_nonce_prehashed(uint64_t handle,
                                                         const struct ByteBuffer *message const,
                                                         struct ExternError *err);

int32_t bbs_blind_sign_context_finish(uint64_t handle,
                                      struct ByteBuffer *blinded_signature,
                                      struct ExternError *err);

int32_t bbs_blind_sign_context_add_message_string(uint64_t handle,
                                                  const char* message const,
                                                  struct ExternError *err);

int32_t bbs_blind_sign_context_add_message_bytes(uint64_t handle,
                                                 const struct ByteBuffer* message const,
                                                 struct ExternError *err);

int32_t bbs_blind_sign_context_add_message_prehashed(uint64_t handle,
                                                     const struct ByteBuffer* message const,
                                                     struct ExternError *err);

int32_t bbs_blind_sign_context_set_secret_key(uint64_t handle,
                                              const struct ByteBuffer* secret_key const,
                                              struct ExternError *err);

int32_t bbs_blind_sign_context_set_public_key(uint64_t handle,
                                              const struct ByteBuffer* public_key const,
                                              struct ExternError *err);

int32_t bbs_blind_sign_context_set_commitment(uint64_t handle,
                                              const struct ByteBuffer* public_key const,
                                              struct ExternError *err);

uint64_t bbs_blind_sign_context_init(struct ExternError *err);

int32_t bbs_blind_signature_size(void);

int32_t bbs_create_proof_context_finish(uint64_t handle, struct ByteBuffer *proof, struct ExternError *err);

int32_t bbs_create_proof_context_set_public_key(uint64_t handle,
                                                const ByteArray *public_key const,
                                                struct ExternError *err);

int32_t bbs_create_proof_context_set_signature(uint64_t handle,
                                               const ByteArray *signature const,
                                               struct ExternError *err);

int32_t bbs_create_proof_context_set_nonce_string(uint64_t handle,
                                                  const char *message const,
                                                  struct ExternError *err);

int32_t bbs_create_proof_context_set_nonce_bytes(uint64_t handle,
                                                 const struct ByteBuffer *message const,
                                                 struct ExternError *err);

int32_t bbs_create_proof_context_set_nonce_prehashed(uint64_t handle,
                                                     const struct ByteBuffer *message const,
                                                     struct ExternError *err);

int32_t bbs_create_proof_context_add_proof_message_string(uint64_t handle,
                                                          const char* message const,
                                                          proof_message_t xtype,
                                                          const struct ByteBuffer *blinding_factor const,
                                                          struct ExternError err);

int32_t bbs_create_proof_context_add_proof_message_bytes(uint64_t handle,
                                                         const struct ByteBuffer message const,
                                                         proof_message_t xtype,
                                                         const struct ByteBuffer *blinding_factor const,
                                                         struct ExternError err);

int32_t bbs_create_proof_context_add_proof_message_prehashed(uint64_t handle,
                                                             const struct ByteBuffer message const,
                                                             proof_message_t xtype,
                                                             const struct ByteBuffer *blinding_factor const,
                                                             struct ExternError err);

uint64_t bbs_create_proof_context_init(struct ExternError *err);

int32_t bbs_sign_context_add_message_string(uint64_t handle,
                                            const char* message const,
                                            struct ExternError *err);

int32_t bbs_sign_context_add_message_bytes(uint64_t handle,
                                           const struct ByteBuffer* message const,
                                           struct ExternError *err);

int32_t bbs_sign_context_add_message_prehashed(uint64_t handle,
                                               const struct ByteBuffer* message const,
                                               struct ExternError *err);

int32_t bbs_sign_context_set_secret_key(uint64_t handle,
                                        const struct ByteBuffer* secret_key const,
                                        struct ExternError *err);

int32_t bbs_sign_context_set_public_key(uint64_t handle,
                                        const struct ByteBuffer* public_key const,
                                        struct ExternError *err);

int32_t bbs_sign_context_finish(uint64_t handle, struct ByteBuffer *signature, struct ExternError *err);

uint64_t bbs_sign_context_init(struct ExternError *err);

int32_t bbs_signature_size(void);

int32_t bbs_verify_context_add_message_bytes(uint64_t handle,
                                             const ByteArray *message const,
                                             struct ExternError *err);

int32_t bbs_verify_context_add_message_prehashed(uint64_t handle,
                                                 const ByteArray *message const,
                                                 struct ExternError *err);

int32_t bbs_verify_context_add_message_string(uint64_t handle,
                                              const char* message const,
                                              struct ExternError *err);

int32_t bbs_verify_context_set_public_key(uint64_t handle,
                                          const ByteArray *public_key const,
                                          struct ExternError *err);
int32_t bbs_verify_context_set_signature(uint64_t handle,
                                         const ByteArray *signature const,
                                         struct ExternError *err);

int32_t bbs_verify_context_finish(uint64_t handle, struct ExternError *err);

uint64_t bbs_verify_context_init(struct ExternError *err);

int32_t bbs_verify_blind_commitment_context_add_blinded(uint64_t handle,
                                                        uint32_t index,
                                                        struct ExternError *err);

int32_t bbs_verify_blind_commitment_context_set_commitment(uint64_t handle,
                                                           const struct ByteBuffer* public_key const,
                                                           struct ExternError *err);

int32_t bbs_verify_blind_commitment_context_set_challenge_hash(uint64_t handle,
                                                               const ByteArray *challenge_hash const,
                                                               struct ExternError *err);

int32_t bbs_verify_blind_commitment_context_set_public_key(uint64_t handle,
                                                           const struct ByteBuffer *public_key const,
                                                           struct ExternError *err);

int32_t bbs_verify_blind_commitment_context_set_nonce_string(uint64_t handle,
                                                             const char *message const,
                                                             struct ExternError *err);

int32_t bbs_verify_blind_commitment_context_set_nonce_bytes(uint64_t handle,
                                                            const struct ByteBuffer *message const,
                                                            struct ExternError *err);

int32_t bbs_verify_blind_commitment_context_set_nonce_prehashed(uint64_t handle,
                                                                const struct ByteBuffer *message const,
                                                                struct ExternError *err);

int32_t bbs_verify_blind_commitment_context_set_proof(uint64_t handle,
                                                      const struct ByteBuffer *proof const,
                                                      struct ExternError *err);

uint64_t bbs_verify_blind_commitment_context_init(struct ExternError *err);


int32_t bbs_verify_proof_context_add_revealed_index(uint64_t handle,
                                                    uint32_t index,
                                                    struct ExternError *err);

int32_t bbs_verify_proof_context_finish(uint64_t handle, struct ExternError *err);


int32_t bbs_verify_proof_context_set_proof(uint64_t handle,
                                           const struct ByteBuffer *proof const,
                                           struct ExternError *err);

int32_t bbs_verify_proof_context_set_public_key(uint64_t handle,
                                                const struct ByteBuffer *public_key const,
                                                struct ExternError *err);


int32_t bbs_verify_proof_context_set_nonce_string(uint64_t handle,
                                                  const char *message const,
                                                  struct ExternError *err);

int32_t bbs_verify_proof_context_set_nonce_bytes(uint64_t handle,
                                                 const struct ByteBuffer *message const,
                                                 struct ExternError *err);

int32_t bbs_verify_proof_context_set_nonce_prehashed(uint64_t handle,
                                                     const struct ByteBuffer *message const,
                                                     struct ExternError *err);


int32_t bbs_verify_proof_context_add_message_string(uint64_t handle,
                                                    const char *message const,
                                                    struct ExternError *err);

int32_t bbs_verify_proof_context_add_message_bytes(uint64_t handle,
                                                   const struct ByteBuffer *message const,
                                                   struct ExternError *err);

int32_t bbs_verify_proof_context_add_message_prehashed(uint64_t handle,
                                                       const struct ByteBuffer *message const,
                                                       struct ExternError *err);

uint64_t bbs_verify_proof_context_init(struct ExternError *err);

int32_t bls_generate_key(const ByteArray *seed const,
struct ByteBuffer *public_key,
                         struct ByteBuffer *secret_key,
                         struct ExternError *err);

int32_t bls_get_public_key(const ByteArray *secret_key const,
                           struct ByteBuffer *public_key,
                           struct ExternError *err);

int32_t bls_public_key_size(void);

int32_t bls_public_key_to_bbs_key(const ByteArray *d_public_key const,
                                  uint32_t message_count,
                                  struct ByteBuffer *public_key,
                                  struct ExternError *err);

int32_t bls_secret_key_size();

int32_t bls_secret_key_to_bbs_key(const ByteArray *secret_key const,
                                  uint32_t message_count,
                                  struct ByteBuffer *public_key,
                                  struct ExternError *err);
#ifdef __cplusplus
} // extern "C"
#endif

#endif