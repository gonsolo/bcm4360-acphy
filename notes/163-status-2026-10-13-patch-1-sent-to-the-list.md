# 163: patch 1 (b43_bcma_remove use-after-free) sent to linux-wireless

Sent 2026-10-13 00:01 UTC by the user with `git send-email` through Gmail (smtp.googlemail.com:587, app password, libsecret keyring).

- Subject: `[PATCH] wifi: b43: fix use-after-free in b43_bcma_remove()`, From and Signed-off-by Andreas Wendleder <gonsolo@gmail.com>.
- Message-ID `20261013000124.48605-1-gonsolo@gmail.com`;
  https://lore.kernel.org/linux-wireless/20261013000124.48605-1-gonsolo@gmail.com/T/#u
- File: `for-lkml/0001-wifi-b43-fix-use-after-free-in-b43_bcma_remove.patch` (3 insertions, 2 deletions; base mainline v7.3-rc5; Fixes: 96838d61102a, Cc: stable).
- Patchwork: state New, delegated to Johannes Berg. wifibot checks all pass except `cc_maintainers` (not CCed: kvalo, julian.calaby, alessio.ferri,
  jpeisach, m@bues.ch) and a `series_format` warning (no tree name in the subject; `[PATCH wireless]` is the usual form). No v2 needed for either.
- Follow-up: a plain reply to the same thread (In-Reply-To) Cc'ing Johannes, b43-dev, m@bues.ch and alessio.ferri@mythread.it, 02:16 local time.
- Alessio had received the 2.4 GHz mail (notes/162, `for-alessio/`) separately from the user.

## What went wrong on the way (for the next send)
- My first `format-patch` kept the list addresses in the patch's To/Cc headers; `git send-email` uses them, so a "test to myself" would have gone to the
  lists. Test with a header-free copy (`awk` drop of the To/Cc block until the first blank line) and `--suppress-cc=all`.
- An empty option value (`--to-cmd=`) is passed on to `git format-patch`; use `--to-cmd=true --cc-cmd=true` when `sendemail.tocmd`/`cccmd` point at
  `scripts/get_maintainer.pl` outside a kernel tree.
- The Perl modules `perl-authen-sasl`, `perl-io-socket-ssl`, `perl-net-ssleay` are needed for SMTP login (Arch: pacman).
- Gmail needs an app password (2-step verification on); the normal password gives 5.7.9. An app password pasted into a chat has to be revoked.

## Still open for the series
Provenance statement agreed with Alessio, full retest of the final series on both bands, patch 2 on a non-AC card, Alessio's 2.4 GHz RX and 5 GHz download
(notes/162).
