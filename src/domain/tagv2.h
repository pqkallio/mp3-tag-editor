#ifndef _ID3_TAG_EDITOR_DOMAIN_TAGV2_H
#define _ID3_TAG_EDITOR_DOMAIN_TAGV2_H

#include <stdint.h>
#include "../dstructs/hashmap.h"
#include "../mem/mem.h"

#define ID3 "ID3"

typedef struct _tag_v2_header
{
    char id[4];
    uint16_t version;
    unsigned char flags;
    uint32_t size;
} TagV2Header;

typedef struct _tag_v2_frame_header
{
    char *id;
    uint32_t size;
    char flags[2];
    unsigned char has_zero_byte;
} TagV2FrameHeader;

typedef struct _tag_v2_frame
{
    char unique_id[33];
    const MemMap *memmap;
    TagV2FrameHeader header;
    char *body;
} TagV2Frame;

typedef struct _tag_v2
{
    const MemMap *memmap;
    TagV2Header header;
    HashMap *frames;
    size_t frame_count;
} TagV2;

TagV2 *new_tag_v2(const MemMap *memmap, uint16_t version, unsigned char flags, uint32_t size);
void delete_tag_v2(TagV2 *tag);

void add_tag_v2_frame(
    TagV2 *tag,
    const char *id,
    uint32_t size,
    char flags[2],
    const char *body,
    unsigned char has_zero_byte);
const TagV2Frame *get_tag_v2_frame(const TagV2 *tagV2, const char *frame_id);
void delete_tag_v2_frame(TagV2Frame *frame);

#endif /* _ID3_TAG_EDITOR_DOMAIN_TAGV2_H */
