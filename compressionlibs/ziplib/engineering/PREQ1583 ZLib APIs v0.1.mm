<map version="0.8.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1185438433916" ID="Freemind_Link_133036316" MODIFIED="1204201626993" TEXT="REQ7297, REQ7362: Zlib APIs (58)">
<node CREATED="1185438966823" ID="Freemind_Link_880956725" MODIFIED="1186053017661" POSITION="right" TEXT="Advanced Functionality (32)" VSHIFT="3">
<node CREATED="1185438977635" ID="Freemind_Link_694973617" MODIFIED="1185445639532" TEXT="Compress (11)" VSHIFT="22">
<node CREATED="1185439155073" FOLDED="true" ID="Freemind_Link_147280846" MODIFIED="1185441509948" TEXT="deflateInit2">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185454660407" ID="Freemind_Link_1883722352" MODIFIED="1185454855517" TEXT="This is another version of deflateInit with more compression options. The&#xa;fields next_in, zalloc, zfree and opaque must be initialized before by&#xa;the caller"/>
</node>
<node CREATED="1185439160276" FOLDED="true" ID="Freemind_Link_404717511" MODIFIED="1185469236798" TEXT="deflateSetDictionary">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185454886173" ID="Freemind_Link_531256554" MODIFIED="1185454895657" TEXT="Initializes the compression dictionary from the given byte sequence&#xa;without producing any compressed output. This function must be called&#xa;immediately after deflateInit, deflateInit2 or deflateReset, before any&#xa;call of deflate. The compressor and decompressor must use exactly the same&#xa;dictionary"/>
</node>
<node CREATED="1185439175995" FOLDED="true" ID="Freemind_Link_915115746" MODIFIED="1185440009885" TEXT="deflateCopy">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185454924673" ID="Freemind_Link_1414883927" MODIFIED="1185454927173" TEXT="Sets the destination stream as a complete copy of the source stream"/>
</node>
<node CREATED="1185439194463" FOLDED="true" ID="Freemind_Link_464281588" MODIFIED="1185454205876" TEXT="deflateParams">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185454969064" ID="Freemind_Link_1017657503" MODIFIED="1185454976814" TEXT="Dynamically update the compression level and compression strategy.  The&#xa;interpretation of level and strategy is as in deflateInit2.  This can be&#xa;used to switch between compression and straight copy of the input data, or&#xa;to switch to a different kind of input data requiring a different&#xa;strategy. If the compression level is changed, the input available so far&#xa;is compressed with the old level (and may be flushed); the new level will&#xa;take effect only at the next call of deflate()"/>
</node>
<node CREATED="1185439208151" FOLDED="true" ID="Freemind_Link_746495766" MODIFIED="1185440010760" TEXT="deflateReset">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185454942345" ID="Freemind_Link_318416412" MODIFIED="1185454949360" TEXT="This function is equivalent to deflateEnd followed by deflateInit,&#xa;but does not free and reallocate all the internal compression state.&#xa;The stream will keep the same compression level and any other attributes&#xa;that may have been set by deflateInit2"/>
</node>
<node CREATED="1185439363838" FOLDED="true" ID="Freemind_Link_407659424" MODIFIED="1185440011166" TEXT="compress2">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185455206564" ID="Freemind_Link_1806956098" MODIFIED="1185455208689" TEXT="The compress2( ) function attempts to compress sourceLen bytes of data in the buffer source, placing the result in the buffer dest, at the level described by level"/>
</node>
<node CREATED="1185438792463" FOLDED="true" ID="Freemind_Link_1595074907" MODIFIED="1185440011557" TEXT="compressBound">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185455228314" ID="Freemind_Link_788127049" MODIFIED="1185455230704" TEXT="The compressBound() function estimates the size of buffer required to compress sourceLen bytes of data using the compress() or compress2( ) functions. If successful, the value returned is an upper bound for the size of buffer required to compress sourceLen bytes of data, using the parameters stored in stream, in a single call to compress() or compress2()"/>
</node>
<node CREATED="1185439262541" FOLDED="true" ID="Freemind_Link_1052901759" MODIFIED="1185440012026" TEXT="deflateBound">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185454999220" ID="Freemind_Link_1839827444" MODIFIED="1185455005298" TEXT="deflateBound() returns an upper bound on the compressed size after&#xa;deflation of sourceLen bytes.  It must be called after deflateInit()&#xa;or deflateInit2().  This would be used to allocate an output buffer&#xa;for deflation in a single pass, and so would be called before deflate()"/>
</node>
<node COLOR="#990000" CREATED="1185442887760" FOLDED="true" ID="Freemind_Link_441091962" MODIFIED="1186046079532" TEXT="deflateSetHeader">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
<node CREATED="1185444247182" ID="Freemind_Link_463483051" MODIFIED="1185444255213" TEXT="deflateSetHeader() provides gzip header information for when a gzip&#xa;stream is requested by deflateInit2().  deflateSetHeader() may be called&#xa;after deflateInit2() or deflateReset() and before the first call of&#xa;deflate()"/>
</node>
<node COLOR="#990000" CREATED="1185442940401" FOLDED="true" ID="Freemind_Link_1748379045" MODIFIED="1186046080141" TEXT="deflatePrime">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
<node CREATED="1185444291323" ID="Freemind_Link_1435611218" MODIFIED="1185444303729" TEXT="deflatePrime() inserts bits in the deflate output stream.  The intent&#xa;is that this function is used to start off the deflate output with the&#xa;bits leftover from a previous deflate stream when appending to it.  As such,&#xa;this function can only be used for raw deflate, and must be used before the&#xa;first deflate() call after a deflateInit2() or deflateReset()"/>
</node>
<node COLOR="#990000" CREATED="1185442998651" FOLDED="true" ID="Freemind_Link_583330979" MODIFIED="1186046080563" TEXT="deflateTune">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
<node CREATED="1185444334213" ID="Freemind_Link_601336664" MODIFIED="1185444357620" TEXT="Fine tune deflate&apos;s internal compression parameters.  This should only be&#xa;used by someone who understands the algorithm used by zlib&apos;s deflate.  &#xa;deflateTune() can be called after deflateInit() or deflateInit2()"/>
</node>
</node>
<node CREATED="1185438980807" ID="Freemind_Link_1913796850" MODIFIED="1186052919943" TEXT="Decompress (11)" VSHIFT="16">
<node CREATED="1185439084995" FOLDED="true" ID="Freemind_Link_1556376047" MODIFIED="1185440012463" TEXT="inflateInit2">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185455297501" ID="Freemind_Link_96124051" MODIFIED="1185455298985" TEXT="The inflateInit2_() function initializse the decompression system. On entry, strm refers to a user supplied z_stream object (a z_stream_s structure)"/>
</node>
<node CREATED="1185438985729" FOLDED="true" ID="Freemind_Link_855324737" MODIFIED="1185440012916" TEXT="inflateSetDictionary">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185455041360" ID="Freemind_Link_1764409884" MODIFIED="1185455094204" TEXT="Initializes the decompression dictionary from the given uncompressed byte&#xa;sequence. This function must be called immediately after a call of inflate,&#xa;if that call returned Z_NEED_DICT. The dictionary chosen by the compressor&#xa;can be determined from the adler32 value returned by that call of inflate.&#xa;The compressor and decompressor must use exactly the same dictionary .  &#xa;For raw inflate, this function can be called&#xa;immediately after inflateInit2() or inflateReset() and before any call of&#xa;inflate() to set the dictionary"/>
</node>
<node CREATED="1185439011901" FOLDED="true" ID="Freemind_Link_1054128552" MODIFIED="1185440013307" TEXT="inflateSync">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185455110407" ID="Freemind_Link_1841463911" MODIFIED="1185455115407" TEXT="Skips invalid compressed data until a full flush point (see above the&#xa;description of deflate with Z_FULL_FLUSH) can be found, or until all&#xa;available input is skipped. No output is provided"/>
</node>
<node CREATED="1185439019526" FOLDED="true" ID="Freemind_Link_1384135414" MODIFIED="1185440013745" TEXT="inflateReset">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185455132282" ID="Freemind_Link_779566408" MODIFIED="1185455137173" TEXT="This function is equivalent to inflateEnd followed by inflateInit,&#xa;but does not free and reallocate all the internal decompression state.&#xa;The stream will keep attributes that may have been set by inflateInit2"/>
</node>
<node CREATED="1185446015892" FOLDED="true" ID="Freemind_Link_1132055742" MODIFIED="1185446025048" TEXT="inflateSyncPoint">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185454078548" ID="Freemind_Link_1237350700" MODIFIED="1185454080345" TEXT="The inflateSyncPoint() function returns a non-zero value if the compressed data stream referenced by stream is at a synchronisation point"/>
</node>
<node COLOR="#990000" CREATED="1185443698635" FOLDED="true" ID="Freemind_Link_722721362" MODIFIED="1186046081470" TEXT="inflateCopy">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
<node CREATED="1185443727432" ID="Freemind_Link_937249905" MODIFIED="1185443774229" TEXT="Sets the destination stream as a complete copy of the source stream.&#xa;This function can be useful when randomly accessing a large stream.  The&#xa;first pass through the stream can periodically record the inflate state,&#xa;allowing restarting inflate at those points when randomly accessing the&#xa;stream."/>
</node>
<node COLOR="#990000" CREATED="1185443704260" FOLDED="true" ID="Freemind_Link_294374274" MODIFIED="1186046081860" TEXT="inflatePrime">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
<node CREATED="1185443799791" ID="Freemind_Link_425366836" MODIFIED="1185443920932" TEXT="This function inserts bits in the inflate input stream.  The intent is&#xa;that this function is used to start inflating at a bit position in the&#xa;middle of a byte.  This function should only be used with raw inflate, and&#xa;should be used before the first inflate() call after inflateInit2() or&#xa;inflateReset()"/>
</node>
<node COLOR="#990000" CREATED="1185443845323" FOLDED="true" ID="Freemind_Link_1485009752" MODIFIED="1186046082282" TEXT="inflateGetHeader">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
<node CREATED="1185443851932" ID="Freemind_Link_1218492422" MODIFIED="1185443880963" TEXT="inflateGetHeader() requests that gzip header information be stored in the&#xa;provided gz_header structure.  inflateGetHeader() may be called after&#xa;inflateInit2() or inflateReset(), and before the first call of inflate()"/>
</node>
<node COLOR="#990000" CREATED="1185444186682" ID="Freemind_Link_468065221" MODIFIED="1186046082673" TEXT="inflateBackInit">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
</node>
<node COLOR="#990000" CREATED="1185443954885" FOLDED="true" ID="Freemind_Link_4964758" MODIFIED="1186046083095" TEXT="inflateBack">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
<node CREATED="1185443961151" ID="Freemind_Link_101465350" MODIFIED="1185444085870" TEXT="inflateBack() does a raw inflate with a single call using a call-back&#xa;interface for input and output.  inflateBackInit() must be called first to allocate the internal state&#xa;and to initialize the state with the user-provided window buffer.&#xa;inflateBack() may then be used multiple times to inflate a complete, raw&#xa;deflate stream with each call.  inflateBackEnd() is then called to free&#xa;the allocated state. "/>
</node>
<node COLOR="#990000" CREATED="1185444106307" ID="Freemind_Link_1335987477" MODIFIED="1186046083485" TEXT="inflateBackEnd">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
</node>
</node>
<node CREATED="1185444651354" ID="Freemind_Link_711394121" MODIFIED="1185445667126" TEXT="GZ Functions (10)" VSHIFT="18">
<node CREATED="1185453188157" ID="Freemind_Link_285044704" MODIFIED="1185453610876" TEXT="General" VSHIFT="-9">
<node CREATED="1185440207463" FOLDED="true" ID="Freemind_Link_909123755" MODIFIED="1185440265385" TEXT="gzseek">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185453310189" ID="Freemind_Link_1364901659" MODIFIED="1185453313564" TEXT="The gzseek() function sets the file-position indicator for the compressed file stream file. The file-position indicator controls where the next read or write operation on the compressed file stream take place"/>
</node>
<node CREATED="1185440386901" FOLDED="true" ID="Freemind_Link_771164638" MODIFIED="1185440390416" TEXT="gztell">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185453402985" ID="Freemind_Link_303012133" MODIFIED="1185453405001" TEXT="The gztell() function returns the starting position for the next read or write operation on the compressed file stream file. This position represents the number of bytes from the beginning of file in the uncompressed data"/>
</node>
<node CREATED="1185440453432" FOLDED="true" ID="Freemind_Link_1270407329" MODIFIED="1185440461245" TEXT="gzerror">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185453482360" ID="Freemind_Link_285110037" MODIFIED="1185453483735" TEXT="The gzerror() function returns a string describing the last error to have occurred associated with the open compressed file stream referred to by file. It also sets the location referenced by errnum to an integer value that further identifies the error"/>
</node>
<node CREATED="1185441962526" FOLDED="true" ID="Freemind_Link_1073080305" MODIFIED="1186416728560" TEXT="gzclearerr">
<edge WIDTH="thin"/>
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="flag"/>
<node CREATED="1185453578407" ID="Freemind_Link_633255906" MODIFIED="1185453580548" TEXT="Clears the error and end-of-file flags for file. This is analogous to the clearerr() function in stdio. This is useful for continuing to read a gzip file that is being written concurrently"/>
<node CREATED="1186416744654" HGAP="22" ID="Freemind_Link_1549709550" MODIFIED="1186416823904" TEXT="Not supported in Nokias zlib offering" VSHIFT="-13">
<edge WIDTH="thin"/>
<font ITALIC="true" NAME="SansSerif" SIZE="12"/>
</node>
</node>
</node>
<node CREATED="1185453198470" ID="Freemind_Link_1868736795" MODIFIED="1185453207282" TEXT="Read">
<node CREATED="1185440366932" FOLDED="true" ID="Freemind_Link_1452668119" MODIFIED="1185440371260" TEXT="gzrewind">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185453373939" ID="Freemind_Link_1935913303" MODIFIED="1185453375439" TEXT="The gzrewind() function sets the starting position for the next read on the compressed file stream file to the beginning of file. file must be open for reading"/>
</node>
<node CREATED="1185440426463" FOLDED="true" ID="Freemind_Link_265746965" MODIFIED="1185440462807" TEXT="gzeof">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185453440892" ID="Freemind_Link_1283703470" MODIFIED="1185453444095" TEXT="The gzeof() function shall test the compressed file stream file for end of file. If file was open for reading and end of file has been reached, gzeof() shall return 1 Otherwise, return 0"/>
</node>
<node CREATED="1185441856120" FOLDED="true" HGAP="21" ID="Freemind_Link_88072660" MODIFIED="1186416728560" TEXT="gzungetc" VSHIFT="1">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="flag"/>
<node CREATED="1185453490376" ID="Freemind_Link_1897236915" MODIFIED="1186416799623" TEXT="Push one character back onto the compressed file stream to be read again later. Only one character of push-back is allowed. The pushed character will be discarded if the stream is repositioned with gzseek() or gzrewind()" VSHIFT="2"/>
<node CREATED="1186416744654" HGAP="21" ID="Freemind_Link_1735760255" MODIFIED="1186416825263" TEXT="Not supported in Nokias zlib offering" VSHIFT="-20">
<font ITALIC="true" NAME="SansSerif" SIZE="12"/>
</node>
</node>
<node CREATED="1185441944135" FOLDED="true" ID="Freemind_Link_1931326597" MODIFIED="1186416728560" TEXT="gzdirect">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="flag"/>
<node CREATED="1185453550939" ID="Freemind_Link_1402267409" MODIFIED="1185453552360" TEXT="Since zlib can open non gzip&apos;d files transparently, gzdirect() returns 1 if reading and doing so transparently, otherwise zero"/>
<node CREATED="1186416744654" HGAP="24" ID="Freemind_Link_418829300" MODIFIED="1186416826310" TEXT="Not supported in Nokias zlib offering" VSHIFT="-11">
<font ITALIC="true" NAME="SansSerif" SIZE="12"/>
</node>
</node>
</node>
<node CREATED="1185453207860" ID="Freemind_Link_1701401883" MODIFIED="1185453613110" TEXT="Write" VSHIFT="14">
<node CREATED="1185440403870" FOLDED="true" ID="Freemind_Link_507767496" MODIFIED="1185440408213" TEXT="gzsetparams">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185453258845" ID="Freemind_Link_69268815" MODIFIED="1185453261954" TEXT="The gzsetparams() function sets the compression level and compression strategy on the compressed file stream referenced by file. The compressed file stream must be open in a write mode. The level and strategy are as defined in deflateInit2()"/>
</node>
<node CREATED="1185440175526" FOLDED="true" ID="Freemind_Link_381125509" MODIFIED="1185440206979" TEXT="gzflush">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185453346829" ID="Freemind_Link_1756466188" MODIFIED="1185453349610" TEXT="The gzflush() function flushes pending output to the compressed file stream identified by file, which must be open for writing"/>
</node>
</node>
</node>
</node>
<node CREATED="1185441779432" ID="Freemind_Link_1939150584" MODIFIED="1185442917057" POSITION="left" TEXT="Data Structures" VSHIFT="-17">
<node CREATED="1185441802807" HGAP="22" ID="Freemind_Link_42412547" MODIFIED="1185441822323" TEXT="z_stream" VSHIFT="-16">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185442788073" ID="Freemind_Link_703381001" MODIFIED="1185442794198" TEXT="gz_header">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
</node>
<node CREATED="1185438529635" FOLDED="true" ID="_" MODIFIED="1186053038255" POSITION="left" TEXT="Basic Functionality (18)" VSHIFT="80">
<node CREATED="1185438547510" ID="Freemind_Link_199527223" MODIFIED="1185445715642" TEXT="Compress (4)">
<node CREATED="1185438614291" FOLDED="true" ID="Freemind_Link_417297353" MODIFIED="1185439995385" TEXT="deflateInit">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185539790801" ID="Freemind_Link_168427168" MODIFIED="1185539798051" TEXT="The deflateInit() function initializes the compression system. On entry, stream refers to a user supplied z_stream object (a z_stream_s structure)"/>
</node>
<node CREATED="1185438636885" FOLDED="true" ID="Freemind_Link_916199765" MODIFIED="1185439996182" TEXT="deflate">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185539747207" ID="Freemind_Link_593894224" MODIFIED="1185539749207" TEXT="The deflate() function attempts to compress data until either the input buffer is empty or the output buffer is full. The stream references a z_stream structure. Before the first call to deflate() this structure should have been initialized by a call to deflateInit2_()"/>
</node>
<node CREATED="1185438640854" FOLDED="true" ID="Freemind_Link_21526873" MODIFIED="1185439996666" TEXT="deflateEnd">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185539729379" ID="Freemind_Link_837075621" MODIFIED="1185539731644" TEXT="The deflateEnd() function frees all allocated state information referenced by stream. All pending output is discarded and unprocessed input is ignored"/>
</node>
<node CREATED="1185438750635" FOLDED="true" ID="Freemind_Link_1564784287" MODIFIED="1185439997104" TEXT="compress">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185539838176" ID="Freemind_Link_1333509061" MODIFIED="1185539839988" TEXT="The compress() function attempts to compress sourceLen bytes of data in the buffer source, placing the result in the buffer dest"/>
</node>
</node>
<node CREATED="1185438552354" ID="Freemind_Link_1595278313" MODIFIED="1185445707345" TEXT="Decompress (4)" VSHIFT="8">
<node CREATED="1185438656885" FOLDED="true" ID="Freemind_Link_1274415088" MODIFIED="1185439997823" TEXT="inflateInit">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185539908707" ID="Freemind_Link_216237167" MODIFIED="1185539912191" TEXT="The inflateInit() function initializes the decompression system. On entry, stream refers to a user supplied z_stream object (a z_stream_s structure)"/>
</node>
<node CREATED="1185438664791" FOLDED="true" ID="Freemind_Link_1595231947" MODIFIED="1185439998229" TEXT="inflate">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185539642801" ID="Freemind_Link_1258871299" MODIFIED="1185539648316" TEXT="The inflate() function shall attempt to decompress data until either the input buffer is empty or the output buffer is full. The stream references a z_stream structure. Before the first call to inflate(), this structure should have been initialized by a call to inflateInit2_()"/>
</node>
<node CREATED="1185438667651" FOLDED="true" ID="Freemind_Link_1849233105" MODIFIED="1185446988673" TEXT="inflateEnd">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185539700785" ID="Freemind_Link_229920207" MODIFIED="1185539703129" TEXT="The inflateEnd() function frees all allocated state information referenced by stream. All pending output is discarded and unprocessed input is ignored"/>
</node>
<node CREATED="1185438700932" FOLDED="true" ID="Freemind_Link_1345683531" MODIFIED="1185439999120" TEXT="uncompress">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185539855957" ID="Freemind_Link_295079543" MODIFIED="1185539856801" TEXT="The uncompress() function attempts to decompress sourceLen bytes of data in the buffer source, placing the result in the buffer dest"/>
</node>
</node>
<node CREATED="1185444616776" ID="Freemind_Link_1238980815" MODIFIED="1185445701829" TEXT="GZ Functions (10)" VSHIFT="17">
<node CREATED="1185453124267" ID="Freemind_Link_463449956" MODIFIED="1185453180439" TEXT="General" VSHIFT="-10">
<node CREATED="1185439756573" ID="Freemind_Link_1873638792" MODIFIED="1185440015026" TEXT="gzopen">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185439789791" ID="Freemind_Link_1634249250" MODIFIED="1185440015823" TEXT="gzdopen">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185440448901" ID="Freemind_Link_1221230986" MODIFIED="1185440460729" TEXT="gzclose">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
</node>
<node CREATED="1185453133267" ID="Freemind_Link_698494347" MODIFIED="1185453137767" TEXT="Read">
<node CREATED="1185439847401" ID="Freemind_Link_1699911596" MODIFIED="1185440016229" TEXT="gzread">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185440112791" ID="Freemind_Link_1087498226" MODIFIED="1185440124151" TEXT="gzgets">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185440129510" ID="Freemind_Link_1562438191" MODIFIED="1185440175166" TEXT="gzgetc">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
</node>
<node CREATED="1185453138142" HGAP="21" ID="Freemind_Link_1829494373" MODIFIED="1185453177595" TEXT="Write" VSHIFT="10">
<node CREATED="1185439904291" ID="Freemind_Link_1099210661" MODIFIED="1185440016604" TEXT="gzwrite">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185440028151" ID="Freemind_Link_1182380379" MODIFIED="1185440085104" TEXT="gzprintf">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185440085620" ID="Freemind_Link_1919341969" MODIFIED="1185440112057" TEXT="gzputs">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185440124416" ID="Freemind_Link_164119808" MODIFIED="1185440129010" TEXT="gzputc">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
</node>
</node>
</node>
<node CREATED="1185439149385" ID="Freemind_Link_693343643" MODIFIED="1185548166035" POSITION="left" TEXT="Other (8)" VSHIFT="11">
<node CREATED="1185439130573" ID="Freemind_Link_900034857" MODIFIED="1185439999651" TEXT="zlibVersion">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185439222526" ID="Freemind_Link_1791068431" MODIFIED="1185440014198" TEXT="adler32">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185439231245" ID="Freemind_Link_1097569190" MODIFIED="1185440014588" TEXT="crc32">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
</node>
<node CREATED="1185445990595" FOLDED="true" ID="Freemind_Link_1564787458" MODIFIED="1185446013564" TEXT="zError">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185454101532" ID="Freemind_Link_1694239488" MODIFIED="1185454103032" TEXT="The zError() function returns a string associated with err. This allows conversion from error code to string for functions, such as compress() and uncompress(), that do not always set the string version of an error"/>
</node>
<node CREATED="1185446025439" FOLDED="true" ID="Freemind_Link_43053082" MODIFIED="1185446032845" TEXT="get_crc_table">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<node CREATED="1185454134626" ID="Freemind_Link_1571426674" MODIFIED="1185454136470" TEXT="The get_crc_table() function returns a pointer to the first of a set of tables used internally to calculate CRC-32 values"/>
</node>
<node COLOR="#990000" CREATED="1185444150073" ID="Freemind_Link_873695456" MODIFIED="1186046085126" TEXT="adler32_combine">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
</node>
<node COLOR="#990000" CREATED="1185444174729" ID="Freemind_Link_1930207752" MODIFIED="1186046085470" TEXT="crc32_combine">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
</node>
<node COLOR="#990000" CREATED="1185444142979" ID="Freemind_Link_11266059" MODIFIED="1186046085829" TEXT="zlibCompileFlags">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="messagebox_warning"/>
</node>
</node>
</node>
</map>
