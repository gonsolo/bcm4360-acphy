#!/usr/bin/env bash
# Send upstream/mail-to-alessio.txt, then series A (upstream/split/A) to Alessio only, with git send-email.
#   tools/upstream/send_to_alessio.sh --dry-run          show what would be sent (needs no password)
#   tools/upstream/send_to_alessio.sh                    send for real (asks to confirm each run)
#   IN_REPLY_TO='<message-id>' tools/upstream/send_to_alessio.sh   put the mail into his thread
# Run from anywhere; needs the sendemail.* git config and the Gmail app password of the sending machine.
set -eu
P=$(cd "$(dirname "$0")/../.." && pwd)
TO='Alessio Ferri <alessio.ferri@mythread.it>'
DRY=; [ "${1:-}" = --dry-run ] && DRY=--dry-run
COMMON="--confirm=always --suppress-cc=all --to-cmd=true --cc-cmd=true $DRY"
cd "$P"
# nothing but Alessio may appear as a recipient
if grep -hE '^(To|Cc):' upstream/split/A/*.patch | grep -q .; then echo "series A patches carry recipient headers, stop"; exit 1; fi
grep -c '^To: Alessio Ferri <alessio.ferri@mythread.it>$' upstream/mail-to-alessio.txt | grep -qx 1
echo "== 1/2 the mail"
# shellcheck disable=SC2086
git send-email $COMMON ${IN_REPLY_TO:+--in-reply-to="$IN_REPLY_TO"} upstream/mail-to-alessio.txt
echo "== 2/2 series A (cover letter + 3 patches)"
# shellcheck disable=SC2086
git send-email $COMMON --to "$TO" upstream/split/A/0*.patch
