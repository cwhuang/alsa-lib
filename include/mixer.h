/****************************************************************************
 *                                                                          *
 *                               mixer.h                                    *
 *                           Mixer Interface                                *
 *                                                                          *
 ****************************************************************************/

/**
 *  \defgroup Mixer Mixer Interface
 *  The mixer interface.
 *  \{
 */

/** Mixer handle */
typedef struct _snd_mixer snd_mixer_t;
/** Mixer elements class handle */
typedef struct _snd_mixer_class snd_mixer_class_t;
/** Mixer element handle */
typedef struct _snd_mixer_elem snd_mixer_elem_t;

/** 
 * \brief Mixer callback function
 * \param mixer Mixer handle
 * \param mask event mask
 * \param elem related mixer element (if any)
 * \return 0 on success otherwise a negative error code
 */
typedef int (*snd_mixer_callback_t)(snd_mixer_t *ctl,
				    unsigned int mask,
				    snd_mixer_elem_t *elem);

/** 
 * \brief Mixer element callback function
 * \param elem Mixer element
 * \param mask event mask
 * \return 0 on success otherwise a negative error code
 */
typedef int (*snd_mixer_elem_callback_t)(snd_mixer_elem_t *elem,
					 unsigned int mask);

/**
 * \brief Compare function for sorting mixer elements
 * \param e1 First element
 * \param e2 Second element
 * \return -1 if e1 < e2, 0 if e1 == e2, 1 if e1 > e2
 */
typedef int (*snd_mixer_compare_t)(const snd_mixer_elem_t *e1,
				   const snd_mixer_elem_t *e2);

/** Mixer element type */
typedef enum _snd_mixer_elem_type {
	/* Simple (legacy) mixer elements */
	SND_MIXER_ELEM_SIMPLE,
	SND_MIXER_ELEM_LAST = SND_MIXER_ELEM_SIMPLE,
} snd_mixer_elem_type_t;

#ifdef __cplusplus
extern "C" {
#endif

int snd_mixer_open(snd_mixer_t **mixer, int mode);
int snd_mixer_close(snd_mixer_t *mixer);
snd_mixer_elem_t *snd_mixer_first_elem(snd_mixer_t *mixer);
snd_mixer_elem_t *snd_mixer_last_elem(snd_mixer_t *mixer);
int snd_mixer_handle_events(snd_mixer_t *mixer);
int snd_mixer_attach(snd_mixer_t *mixer, const char *name);
int snd_mixer_detach(snd_mixer_t *mixer, const char *name);
int snd_mixer_poll_descriptors_count(snd_mixer_t *mixer);
int snd_mixer_poll_descriptors(snd_mixer_t *mixer, struct pollfd *pfds, unsigned int space);
int snd_mixer_load(snd_mixer_t *mixer);
void snd_mixer_free(snd_mixer_t *mixer);
int snd_mixer_wait(snd_mixer_t *mixer, int timeout);
int snd_mixer_set_compare(snd_mixer_t *mixer, snd_mixer_compare_t msort);

snd_mixer_elem_t *snd_mixer_elem_next(snd_mixer_elem_t *elem);
snd_mixer_elem_t *snd_mixer_elem_prev(snd_mixer_elem_t *elem);

int snd_mixer_class_unregister(snd_mixer_class_t *clss);

#ifdef __cplusplus
}
#endif

/**
 *  \defgroup SimpleMixer Simple Mixer Interface
 *  \ingroup Mixer
 *  The simple mixer interface.
 *  \{
 */

/* Simple (legacy) mixer elements API */

/** Mixer simple element channel identificator */
typedef enum _snd_mixer_selem_channel_id {
	/** Unknown */
	SND_MIXER_SCHN_UNKNOWN = -1,
	/** Front left */
	SND_MIXER_SCHN_FRONT_LEFT = 0,
	/** Front right */
	SND_MIXER_SCHN_FRONT_RIGHT,
	/** Front center */
	SND_MIXER_SCHN_FRONT_CENTER,
	/** Rear left */
	SND_MIXER_SCHN_REAR_LEFT,
	/** Rear right */
	SND_MIXER_SCHN_REAR_RIGHT,
	/** Woofer */
	SND_MIXER_SCHN_WOOFER,
	SND_MIXER_SCHN_LAST = 31,
	/** Mono (Front left alias) */
	SND_MIXER_SCHN_MONO = SND_MIXER_SCHN_FRONT_LEFT
} snd_mixer_selem_channel_id_t;

/** Mixer simple element identificator */
typedef struct _snd_mixer_selem_id snd_mixer_selem_id_t;

#ifdef __cplusplus
extern "C" {
#endif

const char *snd_mixer_selem_channel_name(snd_mixer_selem_channel_id_t channel);

int snd_mixer_selem_register(snd_mixer_t *mixer, void *arg,
			     snd_mixer_class_t **classp);
void snd_mixer_selem_get_id(snd_mixer_elem_t *element,
			    snd_mixer_selem_id_t *id);
const char *snd_mixer_selem_get_name(snd_mixer_elem_t *elem);
unsigned int snd_mixer_selem_get_index(snd_mixer_elem_t *elem);
snd_mixer_elem_t *snd_mixer_find_selem(snd_mixer_t *mixer,
				       const snd_mixer_selem_id_t *id);

int snd_mixer_selem_is_playback_mono(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_playback_channel(snd_mixer_elem_t *obj, snd_mixer_selem_channel_id_t channel);
int snd_mixer_selem_is_capture_mono(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_capture_channel(snd_mixer_elem_t *obj, snd_mixer_selem_channel_id_t channel);
int snd_mixer_selem_get_capture_group(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_common_volume(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_playback_volume(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_playback_volume_joined(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_capture_volume(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_capture_volume_joined(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_common_switch(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_playback_switch(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_playback_switch_joined(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_capture_switch(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_capture_switch_joined(snd_mixer_elem_t *elem);
int snd_mixer_selem_has_capture_switch_exclusive(snd_mixer_elem_t *elem);

int snd_mixer_selem_get_playback_volume(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t channel, long *value);
int snd_mixer_selem_get_capture_volume(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t channel, long *value);
int snd_mixer_selem_get_playback_switch(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t channel, int *value);
int snd_mixer_selem_get_capture_switch(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t channel, int *value);
int snd_mixer_selem_set_playback_volume(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t channel, long value);
int snd_mixer_selem_set_capture_volume(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t channel, long value);
int snd_mixer_selem_set_playback_volume_all(snd_mixer_elem_t *elem, long value);
int snd_mixer_selem_set_capture_volume_all(snd_mixer_elem_t *elem, long value);
int snd_mixer_selem_set_playback_switch(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t channel, int value);
int snd_mixer_selem_set_capture_switch(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t channel, int value);
int snd_mixer_selem_set_playback_switch_all(snd_mixer_elem_t *elem, int value);
int snd_mixer_selem_set_capture_switch_all(snd_mixer_elem_t *elem, int value);
void snd_mixer_selem_get_playback_volume_range(snd_mixer_elem_t *elem, 
					       long *min, long *max);
void snd_mixer_selem_set_playback_volume_range(snd_mixer_elem_t *elem, 
					       long min, long max);
void snd_mixer_selem_get_capture_volume_range(snd_mixer_elem_t *elem, 
					      long *min, long *max);
void snd_mixer_selem_set_capture_volume_range(snd_mixer_elem_t *elem, 
					      long min, long max);

size_t snd_mixer_selem_id_sizeof(void);
/** \hideinitializer
 * \brief allocate an invalid #snd_mixer_selem_id_t using standard alloca
 * \param ptr returned pointer
 */
#define snd_mixer_selem_id_alloca(ptr) do { assert(ptr); *ptr = (snd_mixer_selem_id_t *) alloca(snd_mixer_selem_id_sizeof()); memset(*ptr, 0, snd_mixer_selem_id_sizeof()); } while (0)
int snd_mixer_selem_id_malloc(snd_mixer_selem_id_t **ptr);
void snd_mixer_selem_id_free(snd_mixer_selem_id_t *obj);
void snd_mixer_selem_id_copy(snd_mixer_selem_id_t *dst, const snd_mixer_selem_id_t *src);

const char *snd_mixer_selem_id_get_name(const snd_mixer_selem_id_t *obj);

unsigned int snd_mixer_selem_id_get_index(const snd_mixer_selem_id_t *obj);

void snd_mixer_selem_id_set_name(snd_mixer_selem_id_t *obj, const char *val);

void snd_mixer_selem_id_set_index(snd_mixer_selem_id_t *obj, unsigned int val);

void snd_mixer_set_callback(snd_mixer_t *obj, snd_mixer_callback_t val);

void * snd_mixer_get_callback_private(const snd_mixer_t *obj);

void snd_mixer_set_callback_private(snd_mixer_t *obj, void * val);

unsigned int snd_mixer_get_count(const snd_mixer_t *obj);

void snd_mixer_elem_set_callback(snd_mixer_elem_t *obj, snd_mixer_elem_callback_t val);

void * snd_mixer_elem_get_callback_private(const snd_mixer_elem_t *obj);

void snd_mixer_elem_set_callback_private(snd_mixer_elem_t *obj, void * val);

snd_mixer_elem_type_t snd_mixer_elem_get_type(const snd_mixer_elem_t *obj);


#ifdef __cplusplus
}
#endif

/** \} */
/** \} */

